object BinarySearch{

	def Search(nos: Array[Int], num: Int): Int =
	{
		
		var left=0
		var right=nos.length-1
		
		while(left<=right)
		{	
			var mid=(left+right)/2
			if(nos(mid)==num)
				return mid
			
			else if(num<nos(mid))
				right=mid-1
			
			else
				left=mid+1
		}

		return -1
	}
	def main(args : Array[String])
	{
		println("Enter the number of elements")
		var n= Console.readInt
		var nos = new Array[Int](n)
		var toFind: Int = 0
		var i = 0

		for( i<-0 to n-1)
		{
			nos(i)= Console.readInt
		}

		println("Enter the element to be found")
		toFind= Console.readInt

		var sortedArray=nos.sorted
		var index= Search(sortedArray,toFind)

		if(index!= -1)
		{		
			println("The element is found at position "+index)
		}
		
		else
		{
			println("Element not found!")
		}
	}
}
