/*
 * Timmy Wang
 * CMPS101 Tantalo
 * 4/10/2019
 * 
 * List.java
 * Creates a List ADT with a cursor that can add, delete, and move in the list.
 */

class List 
{
	// Node class that is used by List class
	private class Node
	{
		// Fields
		Object data;
		Node next;
		Node prev;
      	
		// Constructor
		Node(Object data) 
		{
			this.data = data; 
			next = null; 
			prev = null;
		}
      
		// toString():  overrides Object's toString() method
      		public String toString() 
		{ 
        	 	return String.valueOf(data); 
     		}
      
      		// equals(): overrides Object's equals() method
      		public boolean equals(Object x)
		{
        	 	boolean eq = false;
        	 	Node that;
        	 	if(x instanceof Node)
			{
        	    		that = (Node) x;
        	    		eq = (this.data).equals(that.data);
        	 	}
        	 	return eq;
      		}
	}

   	// Fields
   	private Node front;
   	private Node back;
	private Node cursor;
   	private int length;
	private int index;

	// Constructor
	List() // Creates a new empty list.
	{
		front = null;
		back = null;
		cursor = null;
		length = 0;
		index = -1;
	}	

	// Access functions
	int length() // Returns the number of elements in this List.
	{
		return length;
	}
	int index() // If cursor is defined, returns the index of the cursor element,
		    // otherwise returns -1.
	{
		if(cursor != null)
		{
			return index;
		}
		return -1;
	}
	Object front() // Returns front element. Pre: length()>0
	{
		if(length <= 0)
		{
			System.err.println("Error: length not greater than 0.");
			return null;
		}
		return front.data;
	}
	Object back() // Returns back element. Pre: length()>0
	{
		if(length <= 0)
                {
                        System.err.println("Error: length not greater than 0.");
                        return null;
                }
		return back.data;
	}
	Object get() // Returns cursor element. Pre: length()>0, index()>=0
	{
		if(length <= 0)
		{
			return null;
		}
		if(index < 0)
		{
			return null;
		}
		return cursor.data;
	}
	public boolean equals(List L) // Returns true if and only if this List and L are the same
			       // integer sequence. The states of the cursors in the two Lists
			       // are not used in determining equality.
	{
		boolean eq = false;
		Node N = front;
		L.moveFront();
		while(N != null && L.get()!=null)
		{
			eq = (N.data).equals(L.get());
			if(eq == false)
				return eq;
			L.moveNext();
			N = N.next;
		}
		if(L.get()!=null && N==null || L.get()==null && N!=null)
		{
			eq = false;
		}
		else if(L.get()==null && N==null)
		{
			eq = true;
		}
		return eq;
	}

	// Manipulation procedures
	void clear() // Resets this List to its original empty state.
	{
		front = null;
		back = null;
		cursor = null;
		length = 0;
		index = -1;
	}
	void moveFront() // If List is non-empty, places the cursor under the front element,
			 // otherwise does nothing.
	{
		if(length > 0)
		{
			cursor = front;
			index = 0;
		}
	}
	void moveBack() // If List is non-empty, places the cursor under the back element,
	 		// otherwise does nothing.
	{
		if(length > 0)
		{
			cursor = back;
			index = length - 1;
		}
	}
	void movePrev() // If cursor is defined and not at front, moves cursor one step toward
	 		// front of this List, if cursor is defined and at front, cursor becomes
			// undefined, if cursor is undefined does nothing.
	{
		if(cursor == null)
			return;
		cursor = cursor.prev;
		index--;
	}
	void moveNext() // If cursor is defined and not at back, moves cursor one step toward
			// back of this List, if cursor is defined and at back, cursor becomes
			// undefined, if cursor is undefined does nothing.
	{
		if(cursor == null)
			return;
		if(cursor == back)
		{
			cursor = null;
			index = -1;
			return;
		}
		cursor = cursor.next;
		index++;
	}
	void prepend(Object data) // Insert new element into this List. If List is non-empty,
			       // insertion takes place before front element.
	{
		Node N = new Node(data);
		if(length == 0)
		{
			front = N;
			back = N;
		}
		else
		{
			front.prev = N;
			N.next = front;
		}
		if(index != -1)
		{
			index++;
		}
		front = N;
		length++;
	}
	void append(Object data) // Insert new element into this List. If List is non-empty,
	 		      // insertion takes place after back element.
	{
		Node N = new Node(data);
		if(length == 0)
		{
			back = N;
			front = N;
		}
		else
		{
			back.next = N;
			N.prev = back;
		}
		back = N;
		length++;
	}
	void insertBefore(Object data) // Insert new element before cursor.
	 			    // Pre: length()>0, index()>=0
	{
                if(length <= 0)
               	{
               	        System.err.println("Error: length not greater than 0.");
               	        return;
               	}
               	if(index < 0)
               	{
               	        System.err.println("Error: index is less than 0.");
               	        return;
               	}
		Node N = new Node(data);
		if(cursor.prev != null)
		{
			(cursor.prev).next = N;
		}
		else
		{
			front = N;
		}
		N.prev = cursor.prev;
		N.next = cursor;
		cursor.prev = N;
		index++;
		length++;
	}
	void insertAfter(Object data) // Inserts new element after cursor.
			 	   // Pre: length()>0, index()>=0
	{
               	if(length <= 0)
               	{
               	        System.err.println("Error: length not greater than 0.");
                   	return;
               	}
               	if(index < 0)
               	{
               	        System.err.println("Error: index is less than 0.");
               	        return;
               	}
		Node N = new Node(data);
		if(cursor.next != null)
		{
			(cursor.next).prev = N;
		}
		else
		{
			back = N;
		}
		N.next = cursor.next;
		N.prev = cursor;
		cursor.next = N;
		length++;
	}
	void deleteFront() // Deletes the front element. Pre: length()>0
	{
		if(length <= 0)
		{
			System.err.println("Error: length not greater than 0.");
			return;
		}
		front = front.next;
		front.prev = null;
		length--;
		index--;
	}
	void deleteBack() // Deletes the back element. Pre: length()>0
	{
		// Preconditions
		if(length <= 0)
		{
			System.err.println("Error: length not greater than 0.");
			return;
		}
		if( cursor == back )
		{
			index = -1;
			cursor = null;
		}
		if(length==1)
		{
			front = back = null;
		}
		else
		{
			back = back.prev;
			back.next = null;
		}
		length--;
	}
	void delete() // Deletes cursor element, making cursor undefined.
	 	      // Pre: length()>0, index()>=0
		      // Other methods
	{
		// Preconditions
		if(length <= 0)
                {
                        System.err.println("Error: length not greater than 0.");
                        return;
                }
                if(index < 0)
                {
                        System.err.println("Error: index is less than 0.");
                        return;
                }
		if( length>1 )
		{
			if( cursor == front)
			{
				(cursor.next).prev = null;
				front = cursor.next;
			}
			else if( cursor==back )
			{
				(cursor.prev).next = null;
				back = cursor.prev;
			}
			else
			{
				(cursor.prev).next = cursor.next;
				(cursor.next).prev = cursor.prev;
			}
		}
		else
		{
			front = back = cursor = null;
		}
		index = -1;
		length--;
	}
	public String toString() // Overrides Object's toString method. Returns a String
	 			 // representation of this List consisting of a space
	 			 // separated sequence of integers, with front on left.
	{
      		StringBuffer sb = new StringBuffer();
      		Node N = front;

      		while(N!=null)
		{
         		sb.append(" ");
         		sb.append(N.toString());
         		N = N.next;
      		}
      		return new String(sb);
	}
}
