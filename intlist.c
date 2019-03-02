/*  Capilano University
*   Comp 220- Professor Jospeph Fall
*   Authour: Tim Wriglesworth
*   Worked on this Project with Karan Nedungadi
*   Date: 20.01.18   
*   Objectives:
*    • to implement a simple list ADT using a dynamic array;
*    • to review common array algorithms (linear search, count, reverse, etc.);
*    • to introduce dynamic memory management using calloc() and free();
*/

#include <stdio.h>
#include <stdlib.h>
#include "intlist.h"
#include <assert.h>


/*
* Function Prototypes that are not defined in H file.
*
*/
/*
dynamically allocate blocks or memory as to grow the list capacity

*/
void ilistGrow( IntList *list );  


/*
shift all the array elements to the right at given index

*/
void ilistShiftRight( IntList *list, int index );	

/*
 sift all the array elements to the left at given index.
*/
void ilistShiftLeft( IntList *list, int index );


/*len represents "logical" length or array while capacity represents "number total spots". if capacity is the same length
*as as logical length, Capacity needs to be expanded (by a block of memory O(n) opposed to allocate each element per array item)
*/


/*
 * Constructor - return a new, empty list 
 * POST:  ilistLen(list) == 0
 */
IntList ilistNew( )       
{
int capacity =1;
int len = 0;
int* data;
data = (int*)calloc(capacity,sizeof(int));  //allocated 4 bytes to start off- this is not necessary but it is how i implement it.
assert(data != NULL);                       
IntList list= {capacity, data, len};        
return list;                               
}

 /*
 * Destructor - remove all data and free all memory associated with the list 
 * POST: ilistLen(list) == 0	
 */
 void ilistDelete( IntList *list )
 {
	 free(list->data);     // empty list contents
	 list->data = NULL;    
	 list->len = 0;        
	 list->capacity = 0;
	 
	  
 }
 
 
 /*
 * Return the number of items in the list
 */
 int ilistLen( IntList list )
{
	return list.len;
}

/*
 * Print a text representation of this list on STDOUT
 */
void ilistPrint( IntList list  )
{
 int i;

	for(i=0; i<list.len; i++)
	{
		printf("%d\n",list.data[i]);
		
	}
}	

/*
 * Return the item at the given index from the list 
 * PRE: 0<=at && at<ilistLen(list)
 */
int ilistGet( IntList list, int at )
{
assert(0<=at && at<ilistLen(list));     

return list.data[at];	
}

/*
 * Return the number of times the given item occurs in the list 
 */
int ilistCount( IntList list, int item )
{
	int count=0;
	int i;
	for(i=0; i<list.len; i++)
	{ 
      if(list.data[i] == item)    	
	  {
		  count ++;
	  }
	}
return count;
}



/*
 * Search the list for the given item
 * RETURN: the position, pos, such that ilistGet(list, pos)==item OR -1 if the item is not found
 */
int ilistFind( IntList list, int item )
{
	int i;
	for (i=0; i<list.len; i++)
	{
		if (list.data[i]==item)
		{
	      return i;
		}
	}
		
	return -1;
}

/*
 * Append the given item to the list 
 * POST: ilistGet( ilistLen(list)-1 ) == item
 */
void ilistAppend( IntList *list, int item )
{
	ilistGrow(list);      
	list->data[list->len] = item;
	list->len +=1;
	
}
/*
* if logical length is the same as capacity array needs more space allocated. achieve through reallocation of 
* previously allocated memory
*/
void ilistGrow( IntList *list )
{
		
  if (list->len == list->capacity )                                
  {
	 int new_capacity= list->capacity + 10;                      
     list->data= realloc(list->data,new_capacity*sizeof(int));
	 assert(list->data != NULL); 

     list->capacity = new_capacity;                            
    }		
}

/*
* POST: elements >=index shift right 1 place
*
*/
void ilistShiftRight( IntList *list, int index )
{
int i = index;
for(i=list->len-1 ; i>=index ; i--)   
    {
	list->data[i+1]= list->data[i];	  		                
	}
	ilistGrow(list);                  

}

/*
 * Insert the given item into the list at the given location
 * POST: length of list is increased by one, and ilistGet( list, at ) == item
 */
void ilistInsert( IntList *list, int at, int item )
{
	ilistGrow(list);
	ilistShiftRight(list, at);
	list->data[at]= item;
	list->len+=1;
		
}

/*
 * POST: at index remove item by shifting all elements after it 1 to the left
 *
 */
void ilistShiftLeft( IntList *list, int index )
{
	
int i = index;
   for(i=index ; i<=list->len ; i++)   
    {
	list->data[i]= list->data[i+1];	  
	}	
}


/*
 * Remove the given item at the given location from the  list 
 * POST: length of list is reduced by one, item at given location has been removed.
 */
void ilistRemove( IntList *list, int at )

{
assert(at<list->len);	  
ilistShiftLeft(list, at);
list->len-=1;
}

/*
 * Append all items from list2 to list1 
 * POST: length of list1 increased by size of list2 and all items from list2 are appended to list1.
 */
void ilistJoin( IntList *list1, IntList list2 )
{
	int i;
	for (i=0; i<list2.len; i++)     
	{
	ilistAppend(list1, (int)list2.data[i] );
	}	  
}

/*
 * Reverse the order of items in the list
 * POST: items in the list are in reversed order (e.g., first item is now last and visa versa)
 */
void ilistReverse( IntList *list )       
{
	 int temp;
     int start = list->data[0];
	 int end = list->len -1;
	 while (start < end)
	 {
		 temp = list->data[start];
		 list->data[start]=list->data[end];
		 list->data[end]=temp;
		 start++;
		 end--;
	 }
		  
	}
