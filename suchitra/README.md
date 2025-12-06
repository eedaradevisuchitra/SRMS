# Student Record Management System (SRMS)

A C-based console application for managing student records with user authentication and role-based access control.

## Features

- **User Authentication**: Secure login system with role-based access (Admin, Staff, Guest)
- **Student Management**: Add, view, search, edit, and delete student records
- **Data Persistence**: Student data is stored in a text file (`studentdata_list.txt`)
- **Password Masking**: Secure password input during login
- **Linked List Implementation**: Uses dynamic linked list for efficient data management

## User Roles

- **Admin**: Full access to all features (add, edit, delete students)
- **Staff**: Can view and search student records
- **Guest**: Read-only access to student information

## Default Credentials

| Username | Password | Role  |
|----------|----------|-------|
| admin    | admin123 | admin |
| staff1   | staff123 | staff |
| guest    | guest    | guest |

## Files

- `CCC.c` - Main source code
- `CCC.exe` - Compiled executable (Windows)
- `studentdata_list.txt` - Student records database
- `Credentials.txt` - User credentials reference

## Building

### Windows (MinGW)
```bash
gcc -o CCC.exe CCC.c
```

### Linux/Mac
```bash
gcc -o CCC CCC.c
```

## Running the Application

### Windows
```bash
CCC.exe
```

### Linux/Mac
```bash
./CCC
```

## Usage

1. Run the executable
2. Login with your credentials
3. Navigate through the menu based on your role
4. Perform desired operations (add, view, edit, delete students)
5. Exit when done

## Requirements

- C compiler (gcc recommended)
- Windows, Linux, or Mac operating system

## Author

Suchitra

## License

This project is open source and available under the MIT License.
