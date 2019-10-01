/*
 * Timmy Wang
 * CMPS101 Tantalo
 * 4/28/2019
 *
 * Matrix.java
 *
 */

class Matrix
{
	// Entry class used as objects for Matrix
	private class Entry
	{
		//Fields
		int column;
		double value;

		Entry(int col, double val)
		{
			column = col;
			value  = val;
		}

		public String toString()
		{
			StringBuffer sb = new StringBuffer();
			sb.append("(" + column + ", " + value + ") ");
			return new String(sb);
		}

		public boolean equals(Object x)
		{
			boolean eq =  false;
			Entry that;
			if(x instanceof Entry)
			{
				that = (Entry) x;
				eq = (this.column == that.column) && (this.value == that.value);
			}
			return eq;
		}
	}

	//Fields
	private List[] matrix;
	private int size;
	private int NNZ;

	// Constructor
	Matrix(int n) // Makes a new n x n zero Matrix. pre: n>=1
	{
		matrix = new List[n];
		for(int i = 0; i<n; i++)
		{
			matrix[i] = new List();
		}
		size = n;
		NNZ = 0;
	}
	
	// Access functions
	int getSize() // Returns n, the number of rows and columns of this Matrix
	{
		return size;
	}
	int getNNZ() // Returns the number of non-zero entries in this Matrix
	{
		return NNZ;
	}
	public boolean equals(Object x) // overrides Object's equals() method
	{
		boolean eq = false;
		Matrix that;
		if( x instanceof Matrix )
		{
			that = (Matrix) x;
			if(that.getSize() != size)
			{
				return eq;
			}
			for(int i = 0; i<size; i++)
			{
				List P = matrix[i];
				List Q = that.matrix[i];
				eq = P.equals(Q);
				if(eq == false)
				{
					break;
				}
			}
		}
		return eq;
	}

	// Manipulation procedures
	void makeZero() // sets this Matrix to the zero state
	{
		for(int i = 0; i<size; i++)
		{
			List P = matrix[i];
			P.moveFront();
			while(P.get()!=null)
			{
				Entry e = (Entry) P.get();
				int j = e.column;
				changeEntry(i+1,j,0);
				P.moveNext();
			}
		}
		NNZ = 0;
	}
	Matrix copy()// returns a new Matrix having the same entries as this Matrix
	{
		Matrix M = new Matrix(getSize());
		for(int i = 0; i<size; i++)
		{
			List P = matrix[i];
			P.moveFront();
			while(P.get()!=null)
			{
				Entry e = (Entry) P.get();
				M.changeEntry(i+1,e.column,e.value);
				P.moveNext();
			}
		}
		return M;
	}
	void changeEntry(int i, int j, double x) // changes ith row, jth column of this Matrix to x
 						 // pre: 1<=i<=getSize(), 1<=j<=getSize()
	{
		if(i<1 || i>size)
		{
			return;
		}
		if(j<1 || j>size)
		{
			return;
		}
		List P = matrix[i-1];
		P.moveFront();
		if( x!=0 )
		{
			Entry e = new Entry(j, x);
			while(P.get()!=null)
			{
				Entry f = (Entry) P.get();
				if(f.column == j)
				{
					f.value = x;
					return;
				}
				else if(f.column > j)
				{
					P.insertBefore(e);
					NNZ++;
					return;
				}
				P.moveNext();
			}
			P.append(e);
			NNZ++;
			return;
		}
		while(P.get()!=null)
		{
			Entry f = (Entry) P.get();
			if(f.column == j)
			{
				P.delete();
				NNZ--;
				return;
			}
			P.moveNext();
		}
	}
	Matrix scalarMult(double x) // returns a new Matrix that is the scalar product of this Matrix with x
	{
		Matrix scalar = new Matrix(size);
		for(int i =0; i<size; i++)
		{
			List P = matrix[i];
			P.moveFront();
			while(P.get()!=null)
			{
				Entry e = (Entry) P.get();
				int j = e.column;
				double y = x * e.value;
				scalar.changeEntry(i+1,j,y);
				P.moveNext();
			}
		}
		return scalar;
	}
	Matrix add(Matrix M) // returns a new Matrix that is the sum of this Matrix with M
 			     // pre: getSize()==M.getSize()
 			     // if pre not met, return 0 matrix same size as current matrix
	{
		Matrix sum = new Matrix(size);
		if(size!=M.getSize())
		{
			System.err.println("Matrix Error: The two matrixes have different sizes.");
			return sum;
		}
		Matrix N = M.transpose().transpose();
		for(int i = 0; i<size; i++)
		{
			List P = matrix[i];
			List Q = N.matrix[i];
			P.moveFront();
			Q.moveFront();
			while(P.get()!=null && Q.get()!=null)
			{
				Entry e = (Entry) P.get();
				Entry f = (Entry) Q.get();
				if(e.column < f.column)
				{
					sum.changeEntry(i+1,e.column,e.value);
					P.moveNext();
				}
				else if(e.column > f.column)
				{
					sum.changeEntry(i+1,f.column,f.value);
					Q.moveNext();
				}
				else
				{
					sum.changeEntry(i+1,e.column,e.value+f.value);
					P.moveNext();
					Q.moveNext();
				}
			}
			while(P.get()!=null)
			{
				Entry e = (Entry) P.get();
				sum.changeEntry(i+1,e.column,e.value);
				P.moveNext();
			}
			while(Q.get()!=null)
			{
				Entry e = (Entry) Q.get();
				sum.changeEntry(i+1,e.column,e.value);
				Q.moveNext();
			}
		}
		return sum;
	}
	Matrix sub(Matrix M) // returns a new Matrix that is the difference of this Matrix with M
 			     // pre: getSize()==M.getSize()
 			     // if pre not met, return 0 matrix
 	{
		Matrix N = M.scalarMult(-1);
		return add(N);
	}
	Matrix transpose() // returns a new Matrix that is the transpose of this Matrix
	{
		Matrix M = new Matrix(size);
		for(int i = 0; i<size; i++)
		{
			List P = matrix[i];
			P.moveFront();
			while(P.get()!=null)
			{
				Entry e = (Entry) P.get();
				M.changeEntry(e.column,i+1,e.value);
				P.moveNext();
			}
		}
		return M;
	}
	Matrix mult(Matrix M) // returns a new Matrix that is the product of this Matrix with M
 			      // pre: getSize()==M.getSize()
	{
		if(size != M.getSize())
		{
			System.err.println("Matrix Multiply error: sizes not same");
		}
		Matrix T = M.transpose();
		Matrix N = new Matrix(size);
		for(int i = 0; i<size; i++)
		{
			List P = matrix[i];
			for(int j = 0; j<size; j++)
			{
				List Q = T.matrix[j];
				double x = dot(P,Q);
				N.changeEntry(i+1,j+1,x);
			}
		}
		return N;
	}
	// Other functions
	public String toString() // overrides Object's toString() method
	{
		StringBuffer sb = new StringBuffer();
		for(int i = 0; i<size; i++)
		{
			List P = matrix[i];
			P.moveFront();
			if(P.get() != null )
			{
				sb.append((i+1) + ": ");
				while(P.get() !=null)
				{
					Entry e = (Entry) P.get();
					sb.append(e.toString());
					P.moveNext();
				}
				sb.append("\n");
			}
		}
		return new String(sb);
	}
	private static double dot(List P, List Q) // calculates dot product of P and Q
	{
		double dot = 0;
		P.moveFront();
		Q.moveFront();
		while(P.get()!=null && Q.get()!=null)
		{
			Entry e = (Entry) P.get();
			Entry f = (Entry) Q.get();
			if(e.column ==  f.column)
			{
				dot += e.value * f.value;
				P.moveNext();
				Q.moveNext();
			}
			else if(e.column < f.column)
			{
				P.moveNext();
			}
			else
			{
				Q.moveNext();
			}
		}
		return dot;
	}
}
