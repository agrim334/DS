#include<stdio.h>
#include<stdlib.h>
int re = 0;
struct node
{
	int i;
	struct node* next;
};
void printlist(struct node* head)
{
printf("\n");
while(head)
	{
		printf("%d ",head -> i);
		head = head -> next;
	}

}
struct node* createnode(int i)
{
	struct node* temp = (struct node*) malloc(sizeof(struct node));
	temp -> i = i;
	temp -> next = 0;
	return temp;
}

struct node* insert(struct node* head,int i,int pos)
{
	if(!head)
		head = createnode(i);
	else
	{
		if(!pos)
			{
				struct node* t1;
				t1 = createnode(i);
				head->next = t1;
			}
		else
			{
				struct node* t1;
				struct node* t2;
				struct node* t3;
				t1 = head;
				t2 = head -> next;
				int steps = pos - 1;
				while(steps--&&t2&&t1)
				{
					t1 = t1 -> next;
					t2 = t2 -> next;
				}
				t3 = createnode(i);
				t1 -> next = t3;
				t3 -> next = t2; 
			}
	}
	return head;
}
struct node* delete(struct node* head,int pos)
{
	if(!pos)
		{
			struct node* t1;
			t1 = head;
			head = head->next;
			free(t1);
		}
	else
		{
			struct node* t1;
			struct node* t2;
			t1 = head;
			t2 = head -> next;
			int steps = pos - 1;
			while(steps--&&t2&&t1)
			{
				t1 = t1 -> next;
				t2 = t2 -> next;
			}
			if(t2)
			{
				t1->next = t2->next;
				free(t2);
			}
			else
				t1->next = 0;
			
		}
	return head;
}
void merge(struct node** head, struct node** mid,struct node** end)
{
struct node* l1 = *head;
struct node* l2 = (*mid) -> next;
struct node* t2 = (*end) -> next;
(*mid) -> next = 0;
(*end) -> next = 0;
struct node* t1 = 0;



while(l1 && l2)
	{
		if(l1 -> i <= l2 -> i)
		{
			if(!t1)
				{
					*head = l1;
					t1 = l1;
					l1 = l1 -> next;
				}
			else
				{
					t1 -> next = l1;
					l1 = l1 -> next;
					t1 = t1 -> next;
				}
		}
		else
		{
			if(!t1)
				{
					*head = l2;
					t1 = l2;
					l2 = l2 -> next;
				}
			else
				{
					t1 -> next = l2;
					l2 = l2 -> next;
					t1 = t1 -> next;
				}
		}
	}

while(l1)
	{
		t1 -> next = l1;
		t1 = l1;
		l1 = l1 -> next;
	}
while(l2)
	{
		t1 -> next = l2;
		t1 = l2;
		l2 = l2 -> next;
	}
*end = t1;
(*end) -> next = t2;
}
void mergesort(struct node** head, struct node** end)
{
if(*end && *head)
	{
		struct node* mid;
		struct node* t1;
		struct node* t2;
		struct node* newhead;
		struct node* newend;
			
		if(*end == (*head) -> next)
			merge(head,head,end);	
	
		else if(*end != *head)
		{
			t2 = *head;
			t1 = *head;

			while( t2 && t1 != *end && t1 != (*end)-> next)
			{
				t2 = t2 -> next;
				t1 = t1 -> next -> next;
			}
			mid = t2;
			
			mergesort(head,&mid);
			mergesort(&(mid->next),end);
			merge(head,&mid,end);
		}
	}
}

struct node* partition(struct node* head, int x){
if(!head)
    return head;
    struct node* nh;
    struct node* nh2;
    struct node* t2;
    struct node* t1;
    struct node* t3;
    
    t2 = head;
    t1 = head;
    nh = 0;
    nh2 = head;
    t3 = 0;
    while(t2)
    {
        if(t2 -> i < x)
        {
            if(!nh)
            {
                t3 = t2;
                nh = t2;
                if(t1 != t2)
                {
                    t1 -> next = t2 -> next;
                    t2 = t1 -> next;
                }
                else
                {
                    nh2 = t1;
                    t1 = t1 -> next;
                    t2 = t1;
                }
                t3 -> next = 0;
                
            }
            else
            {
                t3 -> next = t2;
                t3 = t3 -> next;
                
                if(t1 != t2)
                {
                    t1 -> next = t2 -> next;
                    t2 = t1 -> next;
                }
                else
                {
                    nh2 = t1;
                    t1 = t1 -> next;
                    t2 = t1;
                }
                t3 -> next = 0;
                             
            }
        }
        else
        {    
            t1 = t2;
            t2 = t2 -> next;
        }
    }
    t3 -> next = nh2;
    head = nh;
    return head;
}
int main()
{
	struct node* head = 0;
	int n,i,pos = 0;
	scanf("%d",&n);
	while(pos<n)
		{
			scanf("%d",&i);
			head = insert(head,i,pos);
			pos++;
		}
	
	/*head = insert(head,90,n-1);
	n++;
	
	head = insert(head,50,0);
	n++;
	
	head = insert(head,20,n/2);
	n++;
	
	printlist(head);
	
	head = delete(head,n/2);
	n--;
	
	head = delete(head,0);
	n--;

	head = delete(head,n-1);
	n--;
	*/
	struct node* end = head;
	while(end->next)
		end = end -> next;
	head = partition(head,3);
	printlist(head);
	return 0;
}