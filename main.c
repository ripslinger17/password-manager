#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

sqlite3 *db;
char *zErrMsg = 0;
int rc;

int addData();
int showData();
int deleteData();
int modifyData();

int main()
{
    short choice;

    rc = sqlite3_open("db.sql", &db);

    if (rc)
    {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return (0);
    }
    else
    {
        fprintf(stderr, "Opened database successfully\n");
    }
    sqlite3_close(db);

    printf("Welcome to Password Manager!\n");
    while (1)
    {
        printf("Enter your choice:\n");
        printf("1. Show All Passwords\n2. Add Password\n3. Delete Password\n4. Modify Password\n5. Exit\n");
        scanf("%hd", &choice);

        switch (choice)
        {
        case 1:
            showData();
            printf("\n");
            break;
        case 2:
            addData();
            printf("\n");
            break;
        case 3:
            deleteData();
            printf("\n");
            break;
        case 4:
            modifyData();
            printf("\n");
            break;
        case 5:
            printf("Exiting");
            exit(0);
            break;
        default:
            printf("Invalid Choice");
        }
    }
    return 0;
}

int modifyData()
{
    char id[10];
    char username[100];
    char password[100];
    char website[100];

    char sql[5000];

    printf("Enter the ID to modify:\n");
    scanf("%s", id);
    printf("Enter New Username:\n");
    scanf("%s", username);
    printf("Enter New Password:\n");
    scanf("%s", password);
    printf("Enter New Website:\n");
    scanf("%s", website);

    rc = sqlite3_open("db.sql", &db);
    if (rc)
    {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    sprintf(sql, "UPDATE passwords SET username='%s', password='%s', website='%s'  WHERE id='%s';", username, password, website, id);

    rc = sqlite3_exec(db, sql, 0, 0, &zErrMsg);

    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    else
    {
        fprintf(stdout, "Records updated successfully\n");
    }

    sqlite3_close(db);
    return 0;
}

int deleteData()
{
    char id[10];
    char sql[5000];

    printf("Enter the ID to delete:\n");
    scanf("%s", id);

    rc = sqlite3_open("db.sql", &db);
    if (rc)
    {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    sprintf(sql, "DELETE FROM passwords WHERE id = %s", id);

    rc = sqlite3_exec(db, sql, 0, 0, &zErrMsg);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    else
    {
        fprintf(stdout, "Records deleted successfully\n");
    }

    sqlite3_close(db);
    return 0;
}

int addData()
{
    char username[100];
    char password[100];
    char website[100];

    char sql[5000];

    printf("Enter Username:\n");
    scanf("%s", username);
    printf("Enter Password:\n");
    scanf("%s", password);
    printf("Enter Website:\n");
    scanf("%s", website);

    rc = sqlite3_open("db.sql", &db);

    if (rc)
    {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    sprintf(sql, "INSERT INTO passwords (username, password, website) VALUES ('%s', '%s', '%s')", username, password, website);

    rc = sqlite3_exec(db, sql, 0, 0, &zErrMsg);

    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    else
    {
        fprintf(stdout, "Records created successfully\n");
    }

    sqlite3_close(db);
    return 0;
}

int showData()
{
    const char *sql = "SELECT * FROM passwords;";

    rc = sqlite3_open("db.sql", &db);
    if (rc)
    {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    sqlite3_stmt *stmt;

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error %s\n", zErrMsg);
        sqlite3_close(db);
        return 0;
    }
    printf("\n--- Passwords ---\n");
    printf("%-5s %-20s %-20s %-20s\n", "ID", "Username", "Password", "Website");
    printf("---------------------------------------------\n");

    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW)
    {
        printf("%-5s %-20s %-20s %-20s\n", sqlite3_column_text(stmt, 0), sqlite3_column_text(stmt, 1), sqlite3_column_text(stmt, 2), sqlite3_column_text(stmt, 3));
    }

    if (rc != SQLITE_DONE)
    {
        fprintf(stderr, "SQL error %s\n", zErrMsg);
    }
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return 0;
}