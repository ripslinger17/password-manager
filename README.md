# password-manager
A simple password manager that stores passwords in database. The password manager is a command line application that allows users to store, retrieve, and delete passwords. The passwords are stored in a SQLite database. The code is written in C and uses the SQLite3 library to interact with database.

## Features
- Store password
- Retrieve password
- Delete password
- Modify password
- List all passwords

## How to use
1. Clone the repository
2. Open the terminal and navigate to the repository
3. Run the following command to compile the code
```
gcc main.c -lsqlite3 -o password_manager
```
or 
```
clang main.c -lsqlite3 -o password_manager
```
4. Run the following command to start the password manager
```
./password_manager
```
(might differ for windows)