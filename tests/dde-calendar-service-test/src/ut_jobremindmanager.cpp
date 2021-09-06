/*
* Copyright (C) 2019 ~ 2020 Uniontech Software Technology Co.,Ltd.
*
* Author:     hejinghai <hejinghai@uniontech.com>
*
* Maintainer: hejinghai <hejinghai@uniontech.com>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "ut_jobremindmanager.h"
#include "../third-party_stub/stub.h"
#include "service_stub.h"

#include <QDBusAbstractInterface>
#include <QDebug>

void stub_callWithArgumentList(QDBus::CallMode mode,
                               const QString &method,
                               const QList<QVariant> &args)
{
    Q_UNUSED(mode);
    Q_UNUSED(method);
    Q_UNUSED(args);
}

ut_jobremindmanager::ut_jobremindmanager()
{
    Stub stub;
    stub.set(ADDR(QDBusAbstractInterface, callWithArgumentList), stub_callWithArgumentList);
    jobRemindManager = new JobRemindManager();
}

void ut_jobremindmanager::SetUp()
{
    Stub stub;
    stub.set(ADDR(QDBusAbstractInterface, callWithArgumentList), stub_callWithArgumentList);
    jobRemindManager = new JobRemindManager();
}

void ut_jobremindmanager::TearDown()
{
    delete jobRemindManager;
    jobRemindManager = nullptr;
}

QList<Job> createJobs()
{
    Job job1;
    job1.Start = QDateTime::fromString("2020-12-21T00:00:00+08:00", Qt::ISODate);
    job1.End = QDateTime::fromString("2020-12-21T23:59:00+08:00", Qt::ISODate);
    job1.AllDay = true;
    job1.Type = 1;
    job1.Description = "";
    job1.ID = 1;
    job1.Ignore = "[]";
    job1.Title = "UT测试A";
    job1.RRule = "FREQ=DAILY;BYDAY=MO,TU,WE,TH,FR;COUNT=3";
    job1.RecurID = 0;
    job1.Remind = "1;09:00";

    Job job2;
    job2.Start = QDateTime::fromString("2020-12-22T00:00:00+08:00", Qt::ISODate);
    job2.End = QDateTime::fromString("2020-12-22T23:59:00+08:00", Qt::ISODate);
    job2.AllDay = true;
    job2.Type = 1;
    job2.Description = "";
    job2.ID = 2;
    job2.Ignore = "[\"2020-12-11T00:00:00+08:00\"]";
    job2.Title = "UT测试B";
    job2.RRule = "FREQ=DAILY;BYDAY=MO,TU,WE,TH,FR;COUNT=2";
    job2.RecurID = 0;
    job2.Remind = "1;09:00";

    Job job3;
    job3.Start = QDateTime::fromString("2020-12-24T00:00:00+08:00", Qt::ISODate);
    job3.End = QDateTime::fromString("2020-12-24T23:59:00+08:00", Qt::ISODate);
    job3.AllDay = true;
    job3.Type = 1;
    job3.Description = "";
    job3.ID = 3;
    job3.Ignore = "[]";
    job3.Title = "UT测试C";
    job3.RRule = "FREQ=DAILY;BYDAY=MO,TU,WE,TH,FR;COUNT=4";
    job3.RecurID = 0;
    job3.Remind = "1;09:00";

    QList<Job> jobs;
    jobs << job1 << job2 << job3;
    return jobs;
}

//void JobRemindManager::CallUiOpenSchedule(const Job &job)
TEST_F(ut_jobremindmanager, CallUiOpenSchedule)
{
    Stub stub;
    qDBusAbstractInterface_callWithArgumentList_stub(stub);
    jobRemindManager->CallUiOpenSchedule(createJobs().at(0));
}

//void JobRemindManager::RemindJob(const Job &job)
TEST_F(ut_jobremindmanager, RemindJob)
{
    Stub stub;
    qDBusAbstractInterface_callWithArgumentList_stub(stub);
    jobRemindManager->RemindJob(createJobs().at(0));
    EXPECT_EQ(jobRemindManager->m_notifymap.size(), 1);
}

//int JobRemindManager::GetRemindAdvanceDays(const QString &remind)
TEST_F(ut_jobremindmanager, GetRemindAdvanceDays)
{
    const QString remind = "1,09:00";
    EXPECT_EQ(jobRemindManager->GetRemindAdvanceDays(remind), -1);
}

//void JobRemindManager::RemindJobLater(const Job &job)
TEST_F(ut_jobremindmanager, RemindJobLater)
{
    jobRemindManager->RemindJobLater(createJobs().at(0));
    EXPECT_EQ(jobRemindManager->m_remindlatertimersmap.size(), 1);
}

//void JobRemindManager::SetJobRemindOneDayBefore(const Job &job)
TEST_F(ut_jobremindmanager, SetJobRemindOneDayBefore_01)
{
    QString remindStr = "";
    QObject::connect(jobRemindManager, &JobRemindManager::ModifyJobRemind, [&](const Job &job, const QString &remind) {
        remindStr = remind;
    });
    jobRemindManager->SetJobRemindOneDayBefore(createJobs().at(0));
    EXPECT_EQ(remindStr, "1;09:00");
}

TEST_F(ut_jobremindmanager, SetJobRemindOneDayBefore_02)
{
    Job job3 = createJobs().at(0);
    job3.AllDay = false;
    QString remindStr = "";
    QObject::connect(jobRemindManager, &JobRemindManager::ModifyJobRemind, [&](const Job &job, const QString &remind) {
        Q_UNUSED(job)
        remindStr = remind;
    });

    jobRemindManager->SetJobRemindOneDayBefore(job3);
    EXPECT_EQ(remindStr, "1440") << remindStr.toStdString();
}

//void JobRemindManager::SetJobRemindTomorrow(const Job &job)
TEST_F(ut_jobremindmanager, SetJobRemindTomorrow_01)
{
    QString remindStr = "";
    QObject::connect(jobRemindManager, &JobRemindManager::ModifyJobRemind, [&](const Job &job, const QString &remind) {
        Q_UNUSED(job)
        remindStr = remind;
    });
    jobRemindManager->SetJobRemindTomorrow(createJobs().at(0));
    EXPECT_EQ(remindStr, "0;09:00");
}

TEST_F(ut_jobremindmanager, SetJobRemindTomorrow_02)
{
    Job job3 = createJobs().at(0);
    job3.AllDay = false;
    QString remindStr = "";
    QObject::connect(jobRemindManager, &JobRemindManager::ModifyJobRemind, [&](const Job &job, const QString &remind) {
        remindStr = remind;
    });

    jobRemindManager->SetJobRemindTomorrow(job3);
    EXPECT_EQ(remindStr, "60");
}

////void JobRemindManager::RemindWorkTimeOut()
TEST_F(ut_jobremindmanager, RemindWorkTimeOut)
{
    jobRemindManager->RemindWorkTimeOut();
    EXPECT_EQ(jobRemindManager->m_timejobmap.size(), 0);
}

//void JobRemindManager::UpdateRemindJobs(const QList<Job> &jobs)
TEST_F(ut_jobremindmanager, UpdateRemindJobs)
{
    jobRemindManager->UpdateRemindJobs(createJobs());
    EXPECT_EQ(jobRemindManager->m_timejobmap.size(), createJobs().size());
}

//void JobRemindManager::ActionInvoked(quint32 id, const QString &actionKey)
TEST_F(ut_jobremindmanager, ActionInvoked)
{
    Stub stub;
    qDBusAbstractInterface_callWithArgumentList_stub(stub);
    jobRemindManager->RemindJob(createJobs().at(0));
    jobRemindManager->RemindJob(createJobs().at(1));
    jobRemindManager->RemindJob(createJobs().at(2));
    jobRemindManager->ActionInvoked(1, "later");
    jobRemindManager->ActionInvoked(2, "one-day-before");
    jobRemindManager->ActionInvoked(3, "tomorrow");
    EXPECT_EQ(jobRemindManager->m_notifymap.size(), 1);
}

//void JobRemindManager::NotifyClosed(quint32 id, quint32 reason)
TEST_F(ut_jobremindmanager, NotifyClosed)
{
    jobRemindManager->NotifyClosed(1, 1);
    jobRemindManager->NotifyClosed(2, 1);
    jobRemindManager->NotifyClosed(3, 2);

    EXPECT_EQ(jobRemindManager->m_notifymap.size(), 0);
}
