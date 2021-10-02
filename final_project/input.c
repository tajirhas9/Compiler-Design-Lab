// programming;
int main() {
    int age;
    char name[20];
    
    printf("Name: ");
    scanf("%s", &name);

    printf("Age: ");
    scanf("%d", &age);

    printf("Hello %s, you are %d years old", name, age);

    return 0;
}