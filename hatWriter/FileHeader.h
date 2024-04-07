struct FileHeader
{
    
};

struct Patient
{
    char name[50];
    char lastName[50];
    int age;
    char gender[20];
    char dateOfBirth[20];
    char address[100];
    char phone[20];
    char email[50];
    char bloodType[5];
    char allergies[100];
    char diseases[100];
    char surgeries[100];
    char observations[255];
};

struct Image
{
    char name[50];
    char type[10];
    int width;
    int height;
    char creation_date[20];
};