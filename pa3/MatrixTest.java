/*
 * MatrixTest.java
 */
class MatrixTest
{
	public static void main(String args[])
	{
		Matrix A = new Matrix(3);
		Matrix B = new Matrix(3);
		
		for(int i = 0; i<3; i++)
		{
			for(int j = 0; j<3; j++)
			{
				A.changeEntry(i,j,i+j);
				B.changeEntry(j,i,j-i);
			}
		}
		System.out.println("A is:");
		System.out.println(A);

		System.out.println("B is:");
		System.out.println(B);

		System.out.println("A*3.25 is:");
		System.out.println(A.scalarMult(3.25));

		System.out.println("A+A+B is:");
		System.out.println(A.add(A).add(B));

		System.out.println("A-B-B is:");
		System.out.println(A.sub(B).sub(B));

		System.out.println("A+B-A is:");
		System.out.println(A.add(B).sub(A));

		System.out.println("Transpose(B) is:");
		System.out.println(B.transpose());

		System.out.println("A*A is:");
		System.out.println(A.mult(A));

		return;
	}
}
