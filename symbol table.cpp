#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct symbtab
{
    char label[10];
    int addr;
    struct symbtab *next;
};

struct symbtab *first = NULL;
struct symbtab *last = NULL;

void insert();
void display();
int search(char lab[]);
void del(char lab[]);
void modify();
void modifyLabel(char lab[]);
void modifyAddress(char lab[]);

int main()
{
    int op;
    char la[10];
    do
    {
        printf("\nSYMBOL TABLE IMPLEMENTATION\n");
        printf("1. INSERT\n");
        printf("2. DISPLAY\n");
        printf("3. DELETE\n");
        printf("4. SEARCH\n");
        printf("5. MODIFY\n");
        printf("6. END\n");
        printf("Enter your option : ");
        scanf("%d", &op);
        switch (op)
        {
        case 1:
            insert();
            break;
        case 2:
            display();
            break;
        case 3:
            printf("Enter the label to delete: ");
            scanf("%s", la);
            del(la);
            break;
        case 4:
            printf("Enter the label to search: ");
            scanf("%s", la);
            if (search(la))
                printf("Label found.\n");
            else
                printf("Label not found.\n");
            break;
        case 5:
            modify();
            break;
        case 6:
            break;
        default:
            printf("Invalid option!\n");
            break;
        }

    } while (op != 6);

    return 0;
}

void insert()
{
    char l[10];
    printf("Enter the label : ");
    scanf("%s", l);
    if (search(l))
    {
        printf("The label already exists. Duplicate can't be inserted\n");
    }
    else
    {
        struct symbtab *p;
        p = (struct symbtab *)malloc(sizeof(struct symbtab));
        strcpy(p->label, l);
        printf("Enter the address : ");
        scanf("%d", &p->addr);
        p->next = NULL;
        if (first == NULL)
        {
            first = p;
            last = p;
        }
        else
        {
            last->next = p;
            last = p;
        }
    }
}

void display()
{
    struct symbtab *p;
    p = first;
    printf("LABEL\tADDRESS\n");
    while (p != NULL)
    {
        printf("%s\t%d\n", p->label, p->addr);
        p = p->next;
    }
}

int search(char lab[])
{
    struct symbtab *p;
    p = first;
    while (p != NULL)
    {
        if (strcmp(p->label, lab) == 0)
            return 1;
        p = p->next;
    }
    return 0;
}

void del(char lab[])
{
    struct symbtab *p, *prev;
    p = first;
    prev = NULL;
    while (p != NULL)
    {
        if (strcmp(p->label, lab) == 0)
        {
            if (prev == NULL)
                first = p->next;
            else
                prev->next = p->next;
            if (p == last)
                last = prev;
            free(p);
            printf("Label deleted successfully.\n");
            return;
        }
        prev = p;
        p = p->next;
    }
    printf("Label not found.\n");
}

void modify()
{

    int choice;
    printf("What do you want to modify?\n");
    printf("1. Label\n");
    printf("2. Address\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    char lab[10];
    printf("Enter the label you want to modify: ");
    scanf("%s", lab);

    if (!search(lab))
    {
        printf("Label not found.\n");
        return;
    }

    switch (choice)
    {
    case 1:
        modifyLabel(lab);
        break;
    case 2:
        modifyAddress(lab);
        break;
    default:
        printf("Invalid choice!\n");
        break;
    }
}

void modifyLabel(char lab[])
{
    char newLabel[10];
    printf("Enter new label for %s: ", lab);
    scanf("%s", newLabel);

    if (search(newLabel))
    {
        printf("The new label already exists. Modification failed.\n");
        return;
    }

    struct symbtab *p;
    p = first;
    while (p != NULL)
    {
        if (strcmp(p->label, lab) == 0)
        {
            strcpy(p->label, newLabel);
            printf("Label modified successfully.\n");
            return;
        }
        p = p->next;
    }
}

void modifyAddress(char lab[])
{
    int newAddress;
    printf("Enter new address for %s: ", lab);
    scanf("%d", &newAddress);

    struct symbtab *p;
    p = first;
    while (p != NULL)
    {
        if (strcmp(p->label, lab) == 0)
        {
            p->addr = newAddress;
            printf("Address modified successfully.\n");
            return;
        }
        p = p->next;
    }
}
