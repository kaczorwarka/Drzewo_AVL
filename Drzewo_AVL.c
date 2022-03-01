#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>

#define N 100

typedef struct drzewo
{
    int dana;
    int balans;
    struct drzewo *lewy;
    struct drzewo *prawy;
}drzewo;

void insertBST(drzewo **T,int key)
{
    if (*T == NULL)
    {
        *T = (drzewo*)malloc(sizeof(drzewo));
        (*T) -> lewy = NULL;
        (*T) -> prawy = NULL;
        (*T) -> dana = key;
    }
    else if(key<(*T)->dana)
    {
        insertBST(&((*T)->lewy),key);
    }
    else if(key>(*T)->dana)
    {
        insertBST(&((*T)->prawy),key);
    }
}

void izp(drzewo *T,int *lv,int clv)
{
    clv ++;
    if (clv > *lv)
        *lv = clv;
    if(T->lewy != NULL)
    {
        izp(T->lewy,lv,clv);
    }
    if(T->prawy != NULL)
    {
        izp(T->prawy,lv,clv);
    }
}

void bfallAVL(drzewo **T)
{
    int l = 0, p = 0;
    if((*T)->lewy != NULL)
    {
        bfallAVL(&((*T)->lewy));
        izp((*T)->lewy,&l,0);
    }
    if((*T)->prawy != NULL)
    {
        bfallAVL(&((*T)->prawy));
        izp((*T)->prawy,&p,0);
    }
    (*T)->balans=l-p;
}

void szukajb(drzewo *T,drzewo **wezel,int key,int *b,drzewo **wezelps,int *ss,int *wybor)
{
    char s='d';
    drzewo *wezelp=NULL;
    while (T!=NULL)
    {
        if(T->balans>1||T->balans<(-1))
        {
            *wybor = 1;
            if(s=='l')
                *ss=0;
            else if(s=='p')
                *ss=1;
            else if(s=='d')
                *ss=-1;
            *wezelps = wezelp;
            *b = T->balans;
            *wezel = T;
            s='d';
        }
        if(key == T->dana)
        {
            return NULL;
        }
        else if(key<T->dana)
        {
            if(*wybor==1)
                *wybor+=1;
            else if(*wybor==2)
                *wybor+=0;
            else if(*wybor==3)
                *wybor+=1;
            s = 'l';
            wezelp = T;
            T = T ->lewy;
        }
        else if(key>T->dana)
        {
            if(*wybor==1)
                *wybor+=2;
            else if(*wybor==3)
                *wybor+=2;
            else if(*wybor==2)
                *wybor+=4;
            s = 'p';
            wezelp=T;
            T = T->prawy;
        }
    }
}

void szukaj(drzewo *T,drzewo **wezel,int key,drzewo **wezelp)
{
    while (T!=NULL)
    {
        if(key == T->dana)
        {
            *wezel = T;
            return NULL;
        }
        else if(key<T->dana)
        {
            *wezelp = T;
            T = T ->lewy;

        }
        else if(key>T->dana)
        {
            *wezelp=T;
            T = T->prawy;
        }
    }
}

void RRrotation(drzewo **T,drzewo **wezelps,int s)
{
    if (s == 0)
    {
        if (*wezelps != NULL)
        {
            drzewo *zastepcze;
            zastepcze = (*T);
            (*wezelps)->lewy = (*T)->prawy;
            zastepcze->prawy = zastepcze->prawy->lewy;
            (*wezelps)->lewy->lewy = zastepcze;
        }
        else
        {
            drzewo *zastepcze;
            zastepcze = (*T)->prawy->lewy;
            (*T)->prawy->lewy = (*T);
            (*T)->prawy = zastepcze;
        }
    }
    else
    {
         if (*wezelps != NULL)
         {
            drzewo *zastepcze;
            zastepcze = (*T);
            (*wezelps)->prawy = (*T)->prawy;
            zastepcze->prawy = zastepcze->prawy->lewy;
            (*wezelps)->prawy->lewy = zastepcze;
         }
         else
         {
            drzewo *zastepcze;
            zastepcze = (*T)->prawy->lewy;
            (*T)->prawy->lewy = (*T);
            (*T)->prawy = zastepcze;
         }
    }
}

void LLrotation(drzewo **T,drzewo **wezelps,int s)
{
    if (s == 0)
    {
        if (*wezelps != NULL)
        {
            drzewo *zastepcze;
            zastepcze = (*T);
            (*wezelps)->lewy = (*T)->lewy;
            zastepcze->lewy = zastepcze->lewy->prawy;
            (*wezelps)->lewy->prawy = zastepcze;
        }
        else
        {
            printf("cokolwiek\n");
            drzewo *zastepcze;
            zastepcze = (*T)->lewy->prawy;
            (*T)->lewy->prawy = (*T);
            (*T)->lewy = zastepcze;
        }
    }
    else
    {
         if (*wezelps != NULL)
         {
            drzewo *zastepcze;
            zastepcze = (*T);
            (*wezelps)->prawy = (*T)->lewy;
            zastepcze->lewy = zastepcze->lewy->prawy;
            (*wezelps)->prawy->prawy = zastepcze;
         }
         else
         {
            drzewo *zastepcze;
            zastepcze = (*T)->lewy->prawy;
            (*T)->lewy->prawy = (*T);
            (*T)->lewy = zastepcze;
         }
    }
}

void RLrotation(drzewo **T,drzewo **wezelps,int s)
{
    LLrotation(&((*T)->prawy),T,1);
    RRrotation(T,wezelps,s);
}

void LRrotation(drzewo **T,drzewo **wezelps,int s)
{
    RRrotation(&((*T)->lewy),T,0);
    LLrotation(T,wezelps,s);
}

void insertAVL(drzewo **T,int key)
{
    int b=0,wybor=0;
    int s;
    drzewo *wezel=NULL,*wezelps = NULL;
    insertBST(T,key);
    bfallAVL(T);
    szukajb(*T,&wezel,key,&b,&wezelps,&s,&wybor);
    if(wezel==*T)
    {
        if(wybor == 5)
            *T = (*T)->prawy;
        else if(wybor==4)
            *T = (*T)->prawy->lewy;
        else if (wybor==2)
            *T = (*T)->lewy;
        else
            *T = (*T)->lewy->prawy;

    }
        if(wybor==2)
            LLrotation(&wezel,&wezelps,s);
        else if(wybor==4)
            RLrotation(&wezel,&wezelps,s);
        else if(wybor==5)
            RRrotation(&wezel,&wezelps,s);
        else if(wybor==6)
            LRrotation(&wezel,&wezelps,s);
}

void printlvl_v2(drzewo *T,int lv,int clv,int d,int* csp,int dnd)
{
    if(clv == lv)
    {
        if (T->dana > 9)
        {
            while ((*csp) < d-1)
            {
                (*csp)++;
                printf(" ");
            }
            printf("%d",T->dana);
            (*csp) += 2;
        }
        else
        {
            while ((*csp) < d)
            {
                (*csp)++;
                printf(" ");
            }
            printf("%d",T->dana);
            (*csp) +=1;
        }
    }
    else
    {
        clv ++;
        if (T->lewy != NULL)
        {
            if (dnd%2 != 0)
                dnd ++;
            printlvl_v2(T->lewy,lv,clv,(d-dnd/2),csp,dnd/2);
        }
        if (T->prawy != NULL)
        {
            if (dnd%2 != 0)
                dnd ++;
            if (T->dana > 9)
                d++;
            printlvl_v2(T->prawy,lv,clv,(d+dnd/2),csp,dnd/2);
        }
    }
}

void graficznie(drzewo *T)
{
    if(T)
    {
        int csp;
        int lv = -1, clv = -1,d,dnd;
        izp(T,&lv,clv);
        //printf("%d\n",lv);
        d = lv * pow(2,lv);
        dnd = d;
        clv ++;
         for(int i=0;i<=lv;i++)
        {
            csp = 0;
            printlvl_v2(T,i,clv,d,&csp,dnd);
            printf("\n");
            printf("\n");
            printf("\n");
        }
    }
}

bool czy_w_tablicy(int liczby[],int war)
{
    for(int i=0;i<N;i++)
    {
        if (liczby[i] == war)
            return true;
    }
    return false;
}

void inorder(drzewo *T)
{
    if (T)
    {
        inorder(T->lewy);
        printf("%d ",T->dana);
        inorder(T->prawy);
    }
}

void preorder(drzewo *T)
{
    if (T)
    {
        printf("%d ",T->dana);
        preorder(T->lewy);
        preorder(T->prawy);
    }
}

void postorder(drzewo *T)
{
    if (T)
    {
        postorder(T->lewy);
        postorder(T->prawy);
        printf("%d ",T->dana);
    }
}


void printAVL(drzewo *T)
{
    int wybor;
    printf("[1] - inorder\n");
    printf("[2] - preorder\n");
    printf("[3] - postorder\n");
    printf("[4] - reprezentacja graficzna\n");
    printf("podaj jaki tryb wypisania\n");
    printf("podaj: ");
    scanf("%d",&wybor);
    switch(wybor)
    {
    case(1):
        {
            inorder(T);
            break;
        }
    case(2):
        {
            preorder(T);
            break;
        }
    case(3):
        {
            postorder(T);
            break;
        }
    case(4):
        {
            graficznie(T);
            break;
        }
    }
}

void bfAVL(drzewo *T,int key)
{
    drzewo *wezel,*wezelp;
    szukaj(T,&wezel,key,&wezelp);
    bfallAVL(&wezel);
    printf("Wspolczynnik zbalansowania = %d\n",wezel->balans);
}

void max_p(drzewo **T,drzewo **Tp)
{
    while((*T)->prawy != NULL)
    {
        *Tp = *T;
        *T=(*T)->prawy;
        max_p(T,Tp);
    }

}
void max_l(drzewo **T,drzewo **Tp)
{
    while((*T)->lewy != NULL)
    {
        *Tp = *T;
        *T=(*T)->lewy;
        max_l(T,Tp);
    }

}

void removeAVL(drzewo *T,int key)
{
    drzewo *wezel,*rl,*rp,*rlp,*rpp,*wezelp;
    szukaj(T,&wezel,key,&wezelp);
    //printf("%d\n",wezel->dana);
    int lvl = -1,lvp= -1;
    if(wezel -> prawy != NULL)
    {
        rp = wezel->prawy;
        if (rp->lewy==NULL)
            rpp = wezel;
        izp(rp,&lvp,-1);
        max_l(&rp,&rpp);
    }
     if(wezel -> lewy != NULL)
     {
        rl = wezel->lewy;
        if(rl->prawy==NULL)
            rlp = wezel;
        izp(rl,&lvl,-1);
        max_p(&rl,&rlp);
     }
    if (wezel -> prawy == NULL && wezel->lewy == NULL)
    {
        //printf("cokolwiek\n");
        if (wezelp->lewy->dana == wezel->dana)
            wezelp -> lewy = NULL;
        else
            wezelp->prawy = NULL;
        free(wezel);
    }
    else if (lvl<lvp)
    {
        // usuwanie rp
        //wezel -> dana = rp->dana;
        if(rpp != wezel)
        {
            wezel -> dana = rp->dana;
            rpp -> lewy = rp->prawy;
        }
        else
            {
            wezel -> dana = rp->dana;
            wezel -> prawy = rp -> prawy;//NULL
            }
        free(rp);
    }
    else
    {
        // usuwanie rl
        //wezel -> dana = rl->dana;
        if(rlp != wezel)
        {
            wezel -> dana = rl->dana;
            rlp -> prawy = rl -> lewy;
        }
        else
        {
            wezel -> dana = rl->dana;
            wezel -> lewy = rl -> lewy;//NULL
        }
        free(rl);
    }


}

void removeALL(drzewo **T)
{
    if(*T!=NULL)
    {
        removeALL(&((*T)->lewy));
        removeALL(&((*T)->prawy));
        free(*T);
    }
}

void rotacja(drzewo **T)
{
    int wybor;
    drzewo *wezelp = NULL,*zastepcze;
    printf("[1] - LL rotation \n");
    printf("[2] - RR rotation \n");
    printf("[3] - LR rotation \n");
    printf("[4] - RL rotation \n");
    printf("podaj: ");
    scanf("%d",&wybor);
    /*
    if(wezel==*T)
    {
        if(wybor == 5)
            *T = (*T)->prawy;
        else if(wybor==4)
            *T = (*T)->prawy->lewy;
        else if (wybor==2)
            *T = (*T)->lewy;
        else
            *T = (*T)->lewy->prawy;

    }
        if(wybor==2)
            LLrotation(&wezel,&wezelps,s);
        else if(wybor==4)
            RLrotation(&wezel,&wezelps,s);
        else if(wybor==5)
            RRrotation(&wezel,&wezelps,s);
        else if(wybor==6)
            LRrotation(&wezel,&wezelps,s);
    */
    switch(wybor)
    {
        case(1):
        {
            zastepcze = (*T)->lewy;
            LLrotation(T,&wezelp,0);
            *T = zastepcze;
            break;
        }
        case(2):
        {
            zastepcze = (*T)->prawy;
            RRrotation(T,&wezelp,0);
            *T = zastepcze;
            break;
        }
        case(3):
        {
            zastepcze = (*T)->lewy->prawy;
            LRrotation(T,&wezelp,0);
            *T = zastepcze;
            break;
        }
        case(4):
        {
            zastepcze = (*T)->prawy->lewy;
            RLrotation(T,&wezelp,0);
            *T = zastepcze;
            break;
        }
    }
}

int main()
{
    drzewo *root = NULL;
    int liczby[N];
    for(int i=0;i<N;i++)
        liczby[i]=-1;
    printf("podaj ile dodac liczb losowych: ");
    int il,key,wybor;
    scanf("%d",&il);
    srand(time(NULL));
    for(int i=0;i<il;i++)
    {
        //printf("cokolwiek\n");
        key = rand()%N;
        while(czy_w_tablicy(liczby,key))
            key = rand()%N;
        liczby[i] = key;
    }
    for(int i=0;i<il;i++)
    {
        insertAVL(&root,liczby[i]);
        graficznie(root);
        printf("-------------------------------------------------\n");

    }
    while(1)
    {
        printf("[1] - dodanie nowego elementu do drzewa\n");
        printf("[2] - wypisanie drzewa\n");
        printf("[3] - wypisanie wspolczynnika zbalansowania dla danego wierzcholka\n");
        printf("[4] - usuniecie wskazanego elementu\n");
        printf("[5] - usuniecie calego drzewa\n");
        printf("[6] - rotacja\n");
        printf("podaj: ");
        scanf("%d",&wybor);
        switch(wybor)
        {
            case(1):
            {
                printf("podaj wartosc\n");
                printf("podaj: ");
                scanf("%d",&key);
                insertAVL(&root,key);
                break;
            }
            case(2):
            {
                printAVL(root);
                printf("\n");
                break;
            }
            case(3):
            {
                printf("podaj wartosc\n");
                printf("podaj: ");
                scanf("%d",&key);
                bfAVL(root,key);
                break;
            }
            case(4):
            {
                if (root != NULL)
                    {
                        printf("podaj wartosc do usuniecia: ");
                        scanf("%d",&key);
                        removeAVL(root,key);
                        break;
                    }
                else
                    printf("drzewo puste\n");
                break;
            }
            case(5):
            {
                removeALL(&root);
                root = NULL;
                break;
            }
            case(6):
                rotacja(&root);
                break;
        }

    }
    return 0;
}
