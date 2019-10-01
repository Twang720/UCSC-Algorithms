/*
 * Sparse.java
 */

import java.io.*;
import java.util.Scanner;

class Sparse
{
	public static void main(String args[]) throws IOException
	{
		Scanner in = null;
		PrintWriter out = null;
		String line = null;
		String[] token = null;
		int n, a, b = 0;

		if(args.length !=2)
		{
			System.err.println("Usage: Sparse infile outfile");
			System.exit(1);
		}

		in = new Scanner(new File(args[0]));

		line = in.nextLine() + " ";
		token = line.split("\\s+");
		n = Integer.parseInt(token[0]);
		a = Integer.parseInt(token[1]);
		b = Integer.parseInt(token[2]);
		
		in.nextLine();
		
		Matrix A = new Matrix(n);
		while(in.hasNextLine())
		{
			line = in.nextLine();
			if(line.equals(""))
			{
				break;
			}
			token = line.split("\\s+");
			int r = Integer.parseInt(token[0]);
			int c = Integer.parseInt(token[1]);
			double v = Double.parseDouble(token[2]);
			A.changeEntry(r,c,v);
		}

		Matrix B = new Matrix(n);
		while(in.hasNextLine())
		{
			line = in.nextLine();
			if(line.equals(""))
			{
				break;
			}
			token = line.split("\\s+");
			int r = Integer.parseInt(token[0]);
			int c = Integer.parseInt(token[1]);
			double v = Double.parseDouble(token[2]);
			B.changeEntry(r,c,v);
		}

		out = new PrintWriter(new FileWriter(args[1]));
		
		out.println("A has " + A.getNNZ() + " non-zero entries:");
		out.println(A);

		out.println("B has " + B.getNNZ() + " non-zero entries:");
		out.println(B);
		
		out.println("(1.5)*A =");
		Matrix C = A.scalarMult(1.5);
		out.println(C);

		out.println("A+B =");
		Matrix D = A.add(B);
		out.println(D);

		out.println("A+A =");
		Matrix E = A.add(A);
		out.println(E);
		
		out.println("B-A =");
		Matrix F = B.sub(A);
		out.println(F);
		
		out.println("A-A =");
		Matrix G = A.sub(A);
		out.println(G);
		
		out.println("Transpose(A) =");
		Matrix H = A.transpose();
		out.println(H);
		
		out.println("A*B =");
		Matrix I = A.mult(B);
		out.println(I);
		
		out.println("B*B =");
		Matrix J = B.mult(B);
		out.println(J);

		in.close();
		out.close();
	}
}
