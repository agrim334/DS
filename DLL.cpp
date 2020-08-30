#include<stdio.h>
#include<stdlib.h>

struct node
{
	int i;
	struct node* next;
	struct node* prev;
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
	temp -> prev = 0;
	return temp;
}

void insert(struct node** head,int i,int pos)
{
	if(!(*head))
		*head = createnode(i);
	else
	{
		if(!pos)
			{
				struct node* t1;
				t1 = createnode(i);
				t1 -> next = (*head);
				(*head) -> prev = t1;
				(*head) = t1;
			}
		else
			{
				struct node* t1;
				struct node* t2;
				t1 = (*head);
				int steps = pos - 1;
				while(steps--&&t1)
				{
					t1 = t1 -> next;
				}
				t2 = createnode(i);
				
				t2 -> next = t1 -> next;
				t2 -> prev = t1;
				t1 -> next = t2;
				if(t2 -> next)
					t2 -> next -> prev = t2;
			}
	}
}
void delete(struct node** head,int pos)
{
	if(!pos)
		{
			struct node* t1;
			t1 = (*head);
			*head = (*head)->next;
			(*head) -> prev = 0;
			free(t1);
		}
	else
		{
			struct node* t1;
			struct node* t2;
			t1 = (*head);
			int steps = pos - 1;
			while(steps--&&t1)
			{
				t1 = t1 -> next;
			}
			
			t1 -> prev -> next = t1 -> next;
			if(t1 -> next)
				t1 -> next -> prev = t1 -> prev;
			free(t1);
			
		}
}
void merge(struct node** head, struct node** mid,struct node** end)
{
struct node* l1 = *head;
struct node* l2 = (*mid) -> next;
struct node* t2 = (*end) -> next;
struct node* t3 = (*head) -> prev;

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
					t1 -> next -> prev = t1;
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
					t1 -> next -> prev = t1;
					l2 = l2 -> next;
					t1 = t1 -> next;
				}
		}
	}

while(l1)
	{
		t1 -> next = l1;
		t1 -> next -> prev = t1;
		t1 = l1;
		l1 = l1 -> next;
	}
while(l2)
	{
		t1 -> next = l2;
		t1 -> next -> prev = t1;
		t1 = l2;
		l2 = l2 -> next;
	}
*end = t1;
(*end) -> next = t2;
(*head) -> prev = t3;

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
int main()
{
	struct node* head = 0;
	int n,i,pos = 0;
	scanf("%d",&n);
	while(pos<n)
		{
			scanf("%d",&i);
			insert(&head,i,pos);
			pos++;
		}
	/*insert(&head,90,n-1);
	n++;
	
	insert(&head,50,0);
	n++;
	
	insert(&head,20,n/2);
	n++;
	
	printlist(head);
	
	 delete(&head,n/2);
	n--;
	
	 delete(&head,0);
	n--;

	delete(&head,n-1);
	n--;
	*/
	struct node* end = head;
	while(end->next)
		end = end -> next;
	mergesort(&head,&end);
	printlist(head);
	return 0;
}