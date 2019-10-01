/*
 * ListTest.java
 */
class ListTest
{
	public static void main(String args[])
	{
		List A = new List();
		List B = new List();
		
		for(int i = 0; i<5; i++)
		{
			Integer e = new Integer(2*i);
			A.append(e);
			B.prepend(e);
		}
		System.out.println("A is:\n" + A);
		System.out.println("B is:\n" + B);

		A.moveFront();
		B.moveFront();
		System.out.println(A.get());
		System.out.println(B.get());
		for(int i = 0; i<3; i++)
		{
			B.deleteFront();
			A.deleteBack();
		}
		
		System.out.println(A);
		System.out.println(B);
		
		A.moveBack();
		B.moveBack();
		Integer i = new Integer(7);
		A.insertBefore(i);
		B.insertAfter(i);
		A.delete();
		B.delete();
		
		System.out.println(A);
		System.out.println(B);
		
		A.clear();
		B.clear();

		System.out.println(A);
		System.out.println(B);
	}
}
