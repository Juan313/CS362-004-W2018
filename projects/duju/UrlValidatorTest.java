

import junit.framework.AssertionFailedError;
import junit.framework.TestCase;

//You can use this as a skeleton for your 3 different test approach
//It is an optional to use this file, you can generate your own test file(s) to test the target function!
// Again, it is up to you to use this file or not!





public class UrlValidatorTest extends TestCase {


   public UrlValidatorTest(String testName) {
      super(testName);
   }

   
   
   public void testManualTest()
   {
//You can use this function to implement your manual testing	   

	    UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	    // https is suppposed to be a valid scheme
//		assertTrue(urlVal.isValid("https://"));
		
		// path: pass the test
		assertFalse(urlVal.isValid("http://google.com/test1//file"));
		
		// UrlValidator urlVal = new UrlValidator(null, allowAllSchemes);
		assertTrue(urlVal.isValid("http://www.google.com"));
//		assertTrue(urlVal.isValid("h3t://255.com/$23"));
		assertTrue(urlVal.isValid("http://google.com/t123?action=edit&mode=up"));
		
//		fail to identify invalid URL authority
		assertTrue(urlVal.isValid("http://.aaa"));
		
		// fail to identify the URL below as a valid URL
//		assertTrue(urlVal.isValid("http://ecampus.oregonstate.edu/services/start/canvas-login.htm"));
		
		// fail to recognize port
//		assertTrue(urlVal.isValid("http://www.google.com:80"));
		
		// fail to recognize schemes other than http
//		assertTrue(urlVal.isValid("telnet://go.au"));

		// fail to test that 256.256.256.256 is invalid
//		assertFalse(urlVal.isValid("http://256.256.256.256/"));
		
//		assertTrue(urlVal.isValid("http://0.0.0.0:80/test1?action=view"));

		
   }
   
   
   public void testYourFirstPartition()
   {
	 //You can use this function to implement your First Partition testing	   
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

	   ResultPair[] authorityPartition = { new ResultPair("www.google.com", true), new ResultPair("go.com", true),
				new ResultPair("go.au", true), new ResultPair("0.0.0.0", true), new ResultPair("255.255.255.255", true),
				new ResultPair("256.256.256.256", false), new ResultPair("255.com", true),
				new ResultPair("1.2.3.4.5", false), new ResultPair("1.2.3.4.", false), new ResultPair("1.2.3", false),
				new ResultPair(".1.2.3.4", false), new ResultPair("go.a", false), new ResultPair("go.a1a", false),
				new ResultPair("go.1aa", false), new ResultPair("aaa.", false), new ResultPair(".aaa", false),
				new ResultPair("aaa", false), new ResultPair("", false) };
	   
	   for (int index = 0; index < authorityPartition.length - 1; index++) {
		   StringBuilder testBuffer = new StringBuilder();
		   testBuffer.append("http://");
		   testBuffer.append(authorityPartition[index].getItem());
//		   assertEquals(testBuffer.toString(), authorityPartition[index].getValidity(), urlVal.isValid(testBuffer.toString()));

		   try {
			   assertEquals(testBuffer.toString(), authorityPartition[index].getValidity(), urlVal.isValid(testBuffer.toString()));
		   } catch(AssertionFailedError e) {
			   System.out.println(e.getMessage());
		   }
		   
		}
	  
   }
   
   public void testYourSecondPartition(){
		 //You can use this function to implement your Second Partition testing	
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

	   ResultPair[] urlPortPartition = { new ResultPair(":80", true), new ResultPair(":65535", true),
				new ResultPair(":0", true), new ResultPair("", true), new ResultPair(":-1", false),
				new ResultPair(":65636", false), new ResultPair(":65a", false), new ResultPair(":a", false), 
				new ResultPair("::80", false)};
	   
	   for (int index = 0; index < urlPortPartition.length - 1; index++) {
		   StringBuilder testBuffer = new StringBuilder();
		   testBuffer.append("http://google.com");
		   testBuffer.append(urlPortPartition[index].getItem());
//		   assertEquals(testBuffer.toString(), urlPortPartition[index].getValidity(), urlVal.isValid(testBuffer.toString()));

		   try {
			   assertEquals(testBuffer.toString(), urlPortPartition[index].getValidity(), urlVal.isValid(testBuffer.toString()));
		   } catch(AssertionFailedError e) {
			   System.out.println(e.getMessage());
		   }
		   
		}
   }
   //You need to create more test cases for your Partitions if you need to 
   
   public void testIsValid()
   {
	   //You can use this function for programming based testing

   }
   


}
