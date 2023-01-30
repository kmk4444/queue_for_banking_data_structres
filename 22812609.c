#include <stdio.h>
#include <stdlib.h>

typedef struct Musteri {
    int hesap_no;
	int gelis;
	int islem_suresi;
	int bekeme_suresi;
}Musteri;

typedef struct Calisan {
    int no;
    int is_busy;
    int last_start;
    int duration;
	int hizmet_suresi;
}Calisan;

// Stack için bir struct yapısı kullanılır
typedef struct Stack {
    Calisan *calisan;
	struct Stack* next;
}Stack;

typedef struct Queue {
    Musteri *musteri;
	struct Queue* next;
}Queue;


int isStackFull(Stack* stack); // stack dolu mu diye bakar
int isStackEmpty(Stack** stack);// stack bos mu diye bakar
void pushStack(Stack**, Calisan *);// stacke bir eleman ekler
Calisan* popStack(Stack** stack);//stackten bir eleman alır
Calisan* peekStack(Stack** stack);// stack'in tepedeki elemanını döner

void enqueue(Queue **,int, int, int);
Musteri* dequeue(Queue** queue);
Musteri* peekQueue(Queue** queue);// queue'in tepedeki elemanını döner

void printQueue(Queue *);
// Driver program to test above functions
int main()
{
   // FILE *output_file_fp;

    Calisan calisan1 = {1, 0,0,0,0};
    Calisan calisan2 = {2, 0,0,0,0};
    Calisan calisan3 = {3, 0,0,0,0};
    Calisan calisan4 = {4, 0,0,0,0};
    Calisan calisan5 = {5, 0,0,0,0};
    Calisan calisan6 = {6, 0,0,0,0};

	Stack* stackCalisan = NULL;
	Queue* musteriQueue = NULL;

	pushStack(&stackCalisan, &calisan1);
	pushStack(&stackCalisan, &calisan2);
	pushStack(&stackCalisan, &calisan3);
	pushStack(&stackCalisan, &calisan4);
	pushStack(&stackCalisan, &calisan5);
	pushStack(&stackCalisan, &calisan6);


	int hesap_no;
	int gelis;
	int islem_suresi;

    while (1){
        scanf("%d", &hesap_no);
       // printf("%d is scanned\n", hesap_no);
        if(hesap_no == -1)
            break;

        scanf("%d", &gelis);
        scanf("%d", &islem_suresi);
        enqueue(&musteriQueue, hesap_no, gelis, islem_suresi);
    }

    int time = 1;
    while(musteriQueue){
        //122 6 1 3 0
        if(calisan1.is_busy && time - calisan1.last_start == calisan1.duration){
            // hizmet verme suresi bitti ve artık tekrar stacake gidebilir
            calisan1.duration= 0;;
            calisan1.is_busy = 0;
            calisan1.last_start = 0;
            pushStack(&stackCalisan, &calisan1);

        }
        if(calisan2.is_busy && time - calisan2.last_start == calisan2.duration){
            // hizmet verme suresi bitti ve artık tekrar stacake gidebilir
            calisan2.duration= 0;;
            calisan2.is_busy = 0;
            calisan2.last_start = 0;
            pushStack(&stackCalisan, &calisan2);

        }
        if(calisan3.is_busy && time - calisan3.last_start == calisan3.duration){
            // hizmet verme suresi bitti ve artık tekrar stacake gidebilir
            calisan3.duration= 0;;
            calisan3.is_busy = 0;
            calisan3.last_start = 0;
            pushStack(&stackCalisan, &calisan3);

        }
        if(calisan4.is_busy && time - calisan4.last_start == calisan4.duration){
            // hizmet verme suresi bitti ve artık tekrar stacake gidebilir
            calisan4.duration= 0;
            calisan4.is_busy = 0;
            calisan4.last_start = 0;
            pushStack(&stackCalisan, &calisan4);

        }
        if(calisan5.is_busy && time - calisan5.last_start == calisan5.duration){
            // hizmet verme suresi bitti ve artık tekrar stacake gidebilir
            calisan5.duration= 0;;
            calisan5.is_busy = 0;
            calisan5.last_start = 0;
            pushStack(&stackCalisan, &calisan5);

        }
        if(calisan6.is_busy && time - calisan6.last_start == calisan6.duration){
            // hizmet verme suresi bitti ve artık tekrar stacake gidebilir
            calisan6.duration= 0;
            calisan6.is_busy = 0;
            calisan6.last_start = 0;
            pushStack(&stackCalisan, &calisan6);
        }
        // Eger musait bir calisan varsa ve sirada bekleyen musteri varsa musteriyi calisana yonlendirwecegiz yoksa, calisanın musait olmasını bekleyceğiz
        while(peekQueue(&musteriQueue) && peekStack(&stackCalisan) && peekQueue(&musteriQueue) ->gelis <= time){
            Musteri *siradakiMusteri = dequeue(&musteriQueue);
            Calisan *musaitCalisan = popStack(&stackCalisan);

            siradakiMusteri->bekeme_suresi = time - siradakiMusteri->gelis;

            musaitCalisan->is_busy = 1;
            musaitCalisan->last_start = time;
            musaitCalisan->duration = siradakiMusteri->islem_suresi;
            musaitCalisan->hizmet_suresi += siradakiMusteri->islem_suresi;

            printf("%d %d %d %d %d\n",
                    siradakiMusteri->hesap_no,
                    musaitCalisan->no,
                    time,
                    time + siradakiMusteri->islem_suresi,
                    siradakiMusteri->bekeme_suresi);
        }

        time++;
    }
    printf("\n");
    printf("%d %d\n", calisan6.no, calisan6.hizmet_suresi);
    printf("%d %d\n", calisan5.no, calisan5.hizmet_suresi);
    printf("%d %d\n", calisan4.no, calisan4.hizmet_suresi);
    printf("%d %d\n", calisan3.no, calisan3.hizmet_suresi);
    printf("%d %d\n", calisan2.no, calisan2.hizmet_suresi);
    printf("%d %d\n", calisan1.no, calisan1.hizmet_suresi);
	return 0;
}

void printQueue(Queue *queue){
    Queue *itr= queue;
    while(itr){
        printf("%d, ",itr->musteri->hesap_no);
        itr = itr->next;
    }
    printf("\n");

}
int isStackEmpty(Stack** stack)
{
	return (*stack) == NULL;
}

// Function to add an item to stack. It increases top by 1
void pushStack(Stack** stack, Calisan *calisan)
{


	if (!(*stack))
    {
        *stack = (Stack *) malloc(sizeof(Stack) * 1);
        (*stack)->next= NULL;
    }else{
        Stack *ptr = (Stack *) malloc(sizeof(Stack) * 1);
        ptr->next = (*stack);
        *stack = ptr;
    }

    (*stack)->calisan = calisan;


	//printf("pushed to stack\n");
}

Calisan* popStack(Stack** stack)
{
	if (isStackEmpty(stack))
    {
        // printf("Stack is empty");
        return NULL;
    }

    Calisan* ptrCalisan = (*stack)->calisan;
    Stack* ptrStack = *stack;
    *stack = ((*stack)->next);
    free(ptrStack);

	return ptrCalisan;
}

// Function to return the top from stack without removing it
Calisan * peekStack(Stack** stack)
{
	if (isStackEmpty(stack))
		return NULL;

	return (*stack)->calisan;
}


void enqueue(Queue **queue,int hesap_no, int gelis, int islem_suresi)
{
    Musteri* musteri = (Musteri *) malloc(sizeof(Musteri) * 1);
    musteri->hesap_no = hesap_no;
    musteri->gelis = gelis;
    musteri->islem_suresi = islem_suresi;

    if( (*queue) == NULL){
        (*queue) = (Queue *) malloc(sizeof(Queue) * 1);
        (*queue)->musteri = musteri;
        (*queue)->next = NULL;
    }else{
        Queue *ptr = *queue;
        while(ptr->next)
            ptr = ptr->next;

        ptr->next = (Queue *) malloc(sizeof(Queue) * 1);
        ptr= ptr->next;
        ptr->musteri = musteri;
        ptr->next = NULL;
    }
}

Musteri* dequeue(Queue** queue)
{
    if(!(*queue))
        return NULL;
    else{
        Queue *ptr = *queue;
        Musteri* musteri = ptr->musteri;

        *queue = (*queue)->next;
        free(ptr);
        return musteri;
    }
}
Musteri* peekQueue(Queue** queue)
{
    if ((*queue) == NULL)
        return NULL;
    return (*queue)->musteri;
}
