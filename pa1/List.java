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
		int data;
		Node next;
		Node prev;
      	
		// Constructor
		Node(int data) 
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
        	    		eq = (this.data==that.data);
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
	int front() // Returns front element. Pre: length()>0
	{
		if(length <= 0)
		{
			System.err.println("Error: length not greater than 0.");
			return -1;
		}
		return front.data;
	}
	int back() // Returns back element. Pre: length()>0
	{
		if(length <= 0)
                {
                        System.err.println("Error: length not greater than 0.");
                        return -1;
                }
		return back.data;
	}
	int get() // Returns cursor element. Pre: length()>0, index()>=0
	{
		if(length <= 0)
		{
			System.err.println("Error: length not greater than 0.");
			return -1;
		}
		if(index < 0)
		{
			System.err.println("Error: index is less than 0.");
			return -1;
		}
		return cursor.data;
	}
	boolean equals(List L) // Returns true if and only if this List and L are the same
			       // integer sequence. The states of the cursors in the two Lists
			       // are not used in determining equality.
	{
		Node N = front;
		int i = L.index();
		L.moveFront();
		while(N != null)
		{
			if(N.data != L.get())
			{
				return false;
			}
			L.moveNext();
			N = N.next;
		}
		if(L.get()!=-1 && N==null || L.get()==-1 && N!=null) return false;
		return true;
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
		if(cursor == front)
		{
			cursor = null;
			index = -1;
			return;
		}
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
	void prepend(int data) // Insert new element into this List. If List is non-empty,
			       // insertion takes place before front element.
	{
		Node N = new Node(data);
		if(length == 0)
		{
			back = N;
		}
		else
		{
			front.prev = N;
			N.next = front;
		}
		front = N;
		length++;
	}
	void append(int data) // Insert new element into this List. If List is non-empty,
	 		      // insertion takes place after back element.
	{
		Node N = new Node(data);
		if(length == 0)
		{
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
	void insertBefore(int data) // Insert new element before cursor.
	 			    // Pre: length()>0, index()>=0
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
		
		Node N = new Node(data);
		if(cursor == null)
			return;
		if(cursor.prev != null)

			(cursor.prev).next = N;
		else
			front = N;

		N.prev = cursor.prev;
		N.next = cursor;
		cursor.prev = N;
		length++;
	}
	void insertAfter(int data) // Inserts new element after cursor.
			 	   // Pre: length()>0, index()>=0
	{
		// Preconditions
                if(length <= 0)
                {
                        System.err.println("Error: length not greater than 0.");
                        return;
                }
                if(index() < 0)
                {
                        System.err.println("Error: index is less than 0.");
                        return;
                }

		Node N = new Node(data);
		if(cursor.next != null)
			(cursor.next).prev = N;

		else
			back = N;

		N.prev = cursor;
		N.next = cursor.next;
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
	}
	void deleteBack() // Deletes the back element. Pre: length()>0
	{
		// Preconditions
		if(length <= 0)
		{
			System.err.println("Error: length not greater than 0.");
			return;
		}

		if( length > 1) {
			back = back.prev;
			back.next = null;
		}
		else back = front = null;
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
                if(index() < 0)
                {
                        System.err.println("Error: index is less than 0.");
                        return;
                }

		if(cursor.prev != null)
			(cursor.prev).next = cursor.next;

		else
			front = front.next;
		
		if(cursor.next != null)
			(cursor.next).prev = cursor.prev;

		else
			back = back.prev;

		cursor = null;
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
	List copy() // Returns a new List representing the same integer sequence as this
		    // List. The cursor in the new list is undefined, regardless of the
		    // state of the cursor in this List. This List is unchanged.
	{
		List L = new List();
		Node N = front;

		while(N != null)
		{
			L.append(N.data);
			N = N.next;
		}
		return L;
	}
	List concat(List L) // Returns a new List which is the concatenation of
			    // this list followed by L. The cursor in the new List
 			    // is undefined, regardless of the states of the cursors
 			    // in this List and L. The states of this List and L are
 			    // unchanged.	
 	{
		// Variables
		List N = new List();
		int x = index();

		// Appending this list
		moveFront();
		while(index() != -1)
		{
			N.append(get());
			moveNext();
		}

		// Resetting cursor
		moveFront();
		while(x > 0)
		{
			moveNext();
			x--;
		}

		// Appending list L
		x = L.index();
		L.moveFront();
		while(L.index() != -1)
		{
			N.append(L.get());
			L.moveNext();
		}
		
		// Resetting cursor
		L.moveFront();
		while(x > 0)
		{
			L.moveNext();
			x--;
		}
		return L;
	}
}

