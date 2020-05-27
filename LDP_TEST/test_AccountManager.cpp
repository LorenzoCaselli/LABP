#include "gtest/gtest.h"
#include "..\Users\lorec\source\repos\LABP\Project1\Conto.h"
#include "..\Users\lorec\source\repos\LABP\Project1\AccountManager.h"

class AccountManagerTest : public ::testing::Test
{
protected:
    AccountManager ac;
    string dir = "C:\\Users\\lorec\\source\\repos\\Project1\\Project1\\Accounts.txt";
    virtual void SetUp() {
        ac = AccountManager(dir);
        ac.createAccount("Principale", "Lorenzo");
        ac.createAccount("Secondario", "Lorenzo");
    }

};


TEST_F(AccountManagerTest, ReadFromFile) {
    AccountManager a = a.readFromFile("C:\\Users\\lorec\\source\\repos\\Project1\\Project1\\Accounts.txt");
    ASSERT_EQ(0, a.getAccountBalance(1));
    ASSERT_EQ("Principale", a.getAccountName(1));
    ASSERT_EQ("Lorenzo", a.getAccountUser(1));
    ASSERT_EQ(0, a.getAccountBalance(2));
    ASSERT_EQ("Secondario", a.getAccountName(2));
    ASSERT_EQ("Lorenzo", a.getAccountUser(2));
}

TEST_F(AccountManagerTest, Constructor2Accounts) {
    
    ASSERT_EQ(0, ac.getAccountBalance(1));
    ASSERT_EQ("Principale", ac.getAccountName(1));
    ASSERT_EQ("Lorenzo", ac.getAccountUser(1));
    ASSERT_EQ(0, ac.getAccountBalance(2));
    ASSERT_EQ("Secondario", ac.getAccountName(2));
    ASSERT_EQ("Lorenzo", ac.getAccountUser(2));
}

TEST_F(AccountManagerTest, CreateAccount) {
    ac.createAccount("Principale", "Pippo");
    
    ASSERT_EQ(0, ac.getAccountBalance(3));
    ASSERT_EQ("Principale", ac.getAccountName(3));
    ASSERT_EQ("Pippo", ac.getAccountUser(3));
}

TEST_F(AccountManagerTest, DeleteAccounts) {
    ac.createAccount("Principale", "Pippo");

    ASSERT_EQ(0, ac.getAccountBalance(3));
    ASSERT_EQ("Principale", ac.getAccountName(3));
    ASSERT_EQ("Pippo", ac.getAccountUser(3));
    ASSERT_EQ(3, ac.getNumberOfAccounts());
    ac.deleteAccount(2);
    ASSERT_EQ(2, ac.getNumberOfAccounts());
    ac.deleteAccount(3);
    ASSERT_EQ(1, ac.getNumberOfAccounts());
}

TEST_F(AccountManagerTest, InsertTransactionGainExpense) {
    ac.createTransaction("gain", 1, 500.5, 27,05,2020);
    ac.createTransaction("expense", 2, 400, 27,05,2020);

    ASSERT_EQ(500.5,ac.getAccountBalance(1));
    ASSERT_EQ(-400, ac.getAccountBalance(2));
}


TEST_F(AccountManagerTest, InsertTransactionTransfer) {
    ac.createTransaction("gain", 1, 500.5, 27, 05, 2020);
    ac.createTransaction("expense", 2, 400, 27, 05, 2020);
    ac.createTransaction("transfer", 1, 100, 27, 05, 2020,2);

    ASSERT_EQ(400.5, ac.getAccountBalance(1));
    ASSERT_EQ(-300, ac.getAccountBalance(2));
}

TEST_F(AccountManagerTest, ModifyTransactions) {
    ac.createTransaction("gain", 1, 500.5, 27, 05, 2020);
    ac.createTransaction("expense", 2, 400, 27, 05, 2020);
    ac.createTransaction("transfer", 1, 100, 27, 05, 2020, 2);

    ac.modifyTransaction(1,1,300,27,05,2020);
    ac.modifyTransaction(2, 1, 300, 27, 05, 2020);
    ASSERT_EQ(200, ac.getAccountBalance(1));
    ASSERT_EQ(-200, ac.getAccountBalance(2));
    ac.modifyTransaction(1, 2, 300, 27, 05, 2020);

    ASSERT_EQ(0, ac.getAccountBalance(1));
    ASSERT_EQ(0, ac.getAccountBalance(2));
}


TEST_F(AccountManagerTest, ModifyTransactionsAndReadFromFile) {
    ac.createTransaction("gain", 1, 500.5, 27, 05, 2020);
    ac.createTransaction("expense", 2, 400, 27, 05, 2020);
    ac.createTransaction("transfer", 1, 100, 27, 05, 2020, 2);

    ac.modifyTransaction(1, 1, 300, 27, 05, 2020);
    ac.modifyTransaction(2, 1, 300, 27, 05, 2020);
    ASSERT_EQ(200, ac.getAccountBalance(1));
    ASSERT_EQ(-200, ac.getAccountBalance(2));

    AccountManager a;
    a=a.readFromFile("C:\\Users\\lorec\\source\\repos\\Project1\\Project1\\Accounts.txt");
    ASSERT_EQ(200, a.getAccountBalance(1));
    ASSERT_EQ(-200, a.getAccountBalance(2));
    ASSERT_EQ(2, a.getNumberOfTransactions(2));
    

}



TEST_F(AccountManagerTest, CancelTransactions) {
    ac.createTransaction("gain", 1, 500.5, 27, 05, 2020);
    ac.createTransaction("expense", 2, 400, 27, 05, 2020);
    ac.createTransaction("transfer", 1, 100, 27, 05, 2020, 2);

    ac.modifyTransaction(1, 1, 300, 27, 05, 2020);
    ac.modifyTransaction(2, 1, 300, 27, 05, 2020);
    ASSERT_EQ(200, ac.getAccountBalance(1));
    ASSERT_EQ(-200, ac.getAccountBalance(2));
    ac.modifyTransaction(1, 2, 300, 27, 05, 2020);
    ac.eraseTransaction(2,1);

    ASSERT_EQ(0, ac.getAccountBalance(1));
    ASSERT_EQ(300, ac.getAccountBalance(2));
}