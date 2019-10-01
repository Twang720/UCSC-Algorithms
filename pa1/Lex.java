/*
 * Timmy Wang
 * CMPS101 Tantalo
 * 4/10/2019
 *
 * Lex.java
 * Takes in strings from the input file, lexographically orders the strings, and prints them in the output file.
 */

import java.io.*;
import java.util.Scanner;

class Lex
{
	// Fields
	private int length;
	private String[] arr;
	private List L;
	
	// Main method
	public static void main(String[] args) throws IOException
	{
		// Variables
		String[] arr;
		List L = new List();
      		Scanner in = null;
		Scanner in2 = null;
      		PrintWriter out = null;
      		String line = null;
      		String[] token = null;
      		int n = 0;
		int length = 0;
		
		// CLA counter checker
      		if(args.length != 2)
		{
        	 	System.err.println("Usage: FileIO infile outfile");
        	 	System.exit(1);
      		}
      		
		// Get number of lines in input file
      		in = new Scanner(new File(args[0]));
      		while( in.hasNextLine() )
		{
			in.nextLine();
        	 	length++;
      		}
		
		// Close scanner
		in.close();
		
		// Updating variables and fields
		in2 = new Scanner(new File(args[0]));
		arr = new String[length];
		
		// Inserting lines from input file into array
		for(int i = 0; i<length; i++)
		{
			arr[i] = in2.nextLine();
		}
		
		// Close scanner 2
		in2.close();

		// Creating and sorting list lexographically
		L.append(n++);
		// Loop through array indexes
		while(n < length)
		{
			L.moveFront();
			// Loop through list and compare to determine location of new element
			while(L.index() != -1)
			{
				if(arr[n].compareTo(arr[L.get()]) < 0)
				{
					System.out.println("successfully put in.");
					L.insertBefore(n);
					break;
				}
				L.moveNext();
			}
			// If element is bigger than all elements in list
			if(L.index()==-1)
			{
				System.out.println("succesfully put in back.");
				L.append(n);
			}
			n++;
		}

		// Printing array to output file based off list
		out = new PrintWriter(new FileWriter(args[1]));
		L.moveFront();
		while(L.index() != -1)
		{
			int x = L.get();
			out.println(arr[x]);
			L.moveNext();
		}

		// Closes writer
		out.close();
	}
}
