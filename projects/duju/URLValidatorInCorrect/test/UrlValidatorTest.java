

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
//	    https is suppposed to be a valid scheme
		assertTrue(urlVal.isValid("https://"));
		
		// path: pass the test
		assertFalse(urlVal.isValid("http://google.com/test1//file"));
		
		assertTrue(urlVal.isValid("http://www.google.com"));
//		assertTrue(urlVal.isValid("h3t://255.com/$23"));
		assertTrue(urlVal.isValid("http://google.com/t123?action=edit&mode=up"));
		
//		fail to identify invalid URL authority
		assertTrue(urlVal.isValid("http://.aaa"));
		
		// fail to identify the URL below as a valid URL
		assertTrue(urlVal.isValid("http://ecampus.oregonstate.edu/services/start/canvas-login.htm"));
		
		// fail to recognize port
		assertTrue(urlVal.isValid("http://www.google.com:80"));
		
		// fail to recognize schemes other than http
		assertTrue(urlVal.isValid("telnet://go.au"));

		// fail to test that 256.256.256.256 is invalid
		assertFalse(urlVal.isValid("http://256.256.256.256/"));
		
		assertTrue(urlVal.isValid("http://0.0.0.0:80/test1?action=view"));

		
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
		   assertEquals(testBuffer.toString(), authorityPartition[index].getValidity(), urlVal.isValid(testBuffer.toString()));

//		   try {
//			   assertEquals(testBuffer.toString(), authorityPartition[index].getValidity(), urlVal.isValid(testBuffer.toString()));
//		   } catch(AssertionFailedError e) {
//			   System.out.println(e.getMessage());
//		   }
		   
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
		   assertEquals(testBuffer.toString(), urlPortPartition[index].getValidity(), urlVal.isValid(testBuffer.toString()));

//		   try {
//			   assertEquals(testBuffer.toString(), urlPortPartition[index].getValidity(), urlVal.isValid(testBuffer.toString()));
//		   } catch(AssertionFailedError e) {
//			   System.out.println(e.getMessage());
//		   }
		   
		}
   }
   
   public void testIsValid()
   {
	   //You can use this function for programming based testing
	   
	    UrlValidator urlVal = new UrlValidator();
		
		//Default is to not print output from passing tests because we are only concerned with failures
		boolean PRINTPASSES = true;

		//Valid schemes
		String[] validSchemes = {"http://", "ftp://", "https://"};
		int numValidSchemes = 3;
		//Invalid schemes
		String[] invalidSchemes = {"htt://", " ", "http:/", "satp://", "httpb://", "123://", "https:://"};
		int numInvalidSchemes = 7;
		//Valid authorities
		String[] validAuthorities = {"yahoo.com", "npr.org", "asu.edu", "disability.gov", "espn.com", "hackerrank.com"};
		int numValidAuthorities = 6;
		//Invalid authorities
		String[] invalidAuthorities = {".comoo", ".orgaa", ".eduxcz", ".gosss", ".uqwe", "..uk", ". cn", "./au"};
		int numInvalidAuthorities = 8;
		//Valid Path Options
		String[] validPaths = {"/page1", "/today", "/yesterday/tomorrow/", "/thisshouldwork", "/123", "/theblackpanther123"};
		int numValidPaths = 6;
		//Invalid Path Options
		String[] invalidPaths = {"$#</.@#@/", "aa//aa/", ",/234", ".gosss", "//3423", "..con", "/123/``/"};
		int numInvalidPaths = 7;


		//Test #1: Valid scheme with valid authority and valid path

		//Out loop for scheme
		for (int i = 0; i < numValidSchemes; i++)
		{
			//Middle loop for authority
			for (int j = 0; j < numValidAuthorities; j++)
			{
				//Inner loop for path
				for (int k = 0; k < numValidPaths; k++)
				{
					String url = "";
					url += validSchemes[i];
					url += validAuthorities[j];
					url += validPaths[k];


					//All of these tests should return true because scheme, authority, and path are all valid.
					if (urlVal.isValid(url))
					{
						if (PRINTPASSES == true)
						{
							System.out.println("Test #1 Url: " + url + " test passed");
						}
					}
					else
					{
						
							System.out.println("Test #1 Url: " + url + " test failed");
						
					}

				}


			}


		}//End Test #1

		

		//Test #2: Valid scheme with invalid authority and valid path

		//Out loop for scheme
		for (int i = 0; i < numValidSchemes; i++)
		{
			//Middle loop for authority
			for (int j = 0; j < numInvalidAuthorities; j++)
			{
				//Inner loop for path
				for (int k = 0; k < numValidPaths; k++)
				{
					String url = "";
					url += validSchemes[i];
					url += invalidAuthorities[j];
					url += validPaths[k];

					//All of these tests should return false since the scheme is invalid
					if (urlVal.isValid(url))
					{
						System.out.println("Test #2 Url: " + url + " test failed");
					}
					else
					{
						if (PRINTPASSES == true)
						{
							System.out.println("Test #2 Url: " + url + " test passed");
						}
					}

				}


			}


		}//End Test #2


		
		//Test #3: Valid scheme with valid authority and invalid path

		//Out loop for scheme
		for (int i = 0; i < numValidSchemes; i++)
		{
			//Middle loop for authority
			for (int j = 0; j < numValidAuthorities; j++)
			{
				//Inner loop for path
				for (int k = 0; k < numInvalidPaths; k++)
				{
					String url = "";
					url += validSchemes[i];
					url += validAuthorities[j];
					url += invalidPaths[k];

					//All of these tests should return false since the scheme is invalid
					if (urlVal.isValid(url))
					{
						System.out.println("Test #3 Url: " + url + " test failed");
					}
					else
					{
						if (PRINTPASSES == true)
						{
							System.out.println("Test #3 Url: " + url + " test passed");
						}
					}

				}


			}


		}//End Test #3
		
		
		
		//Test #4: Valid scheme with invalid authority and invalid path

				//Out loop for scheme
				for (int i = 0; i < numValidSchemes; i++)
				{
					//Middle loop for authority
					for (int j = 0; j < numInvalidAuthorities; j++)
					{
						//Inner loop for path
						for (int k = 0; k < numInvalidPaths; k++)
						{
							String url = "";
							url += validSchemes[i];
							url += invalidAuthorities[j];
							url += invalidPaths[k];

							//All of these tests should return false since the scheme is invalid and authority is invalid
							if (urlVal.isValid(url))
							{
								System.out.println("Test #4 Url: " + url + " test failed");
							}
							else
							{
								if (PRINTPASSES == true)
								{
									System.out.println("Test #4 Url: " + url + " test passed");
								}
							}

						}


					}


				}//End Test #4
		


		//Test #5: Invalid scheme with valid authority and valid path

		//Out loop for scheme
		for (int i = 0; i < numInvalidSchemes; i++)
		{
			//Middle loop for authority
			for (int j = 0; j < numValidAuthorities; j++)
			{
				//Inner loop for path
				for (int k = 0; k < numValidPaths; k++)
				{
					String url = "";
					url += invalidSchemes[i];
					url += validAuthorities[j];
					url += validPaths[k];


					//All of these tests should return true because scheme is invalid
					if (urlVal.isValid(url))
					{
						System.out.println("Test #5 Url: " + url + " test passed");
					}
					else
					{
						if (PRINTPASSES == true)
						{
							System.out.println("Test #5 Url: " + url + " test failed");
						}
					}

				}


			}


		}//End Test #5



		//Test #6: Invalid scheme with invalid authority and valid path

		//Out loop for scheme
		for (int i = 0; i < numInvalidSchemes; i++)
		{
			//Middle loop for authority
			for (int j = 0; j < numInvalidAuthorities; j++)
			{
				//Inner loop for path
				for (int k = 0; k < numValidPaths; k++)
				{
					String url = "";
					url += invalidSchemes[i];
					url += invalidAuthorities[j];
					url += validPaths[k];

					//All of these tests should return false since the scheme and authority are invalid
					if (urlVal.isValid(url))
					{
						System.out.println("Test #6 Url: " + url + " test failed");
					}
					else
					{
						if (PRINTPASSES == true)
						{
							System.out.println("Test #6 Url: " + url + " test passed");
						}
					}

				}


			}


		}//End Test #6

		

		//Test #7: Invalid scheme with valid authority and invalid path

		//Out loop for scheme
		for (int i = 0; i < numInvalidSchemes; i++)
		{
			//Middle loop for authority
			for (int j = 0; j < numValidAuthorities; j++)
			{
				//Inner loop for path
				for (int k = 0; k < numInvalidPaths; k++)
				{
					String url = "";
					url += invalidSchemes[i];
					url += validAuthorities[j];
					url += invalidPaths[k];

					//All of these tests should return false since the path and scheme are invalid
					if (urlVal.isValid(url))
					{
						System.out.println("Test #7 Url: " + url + " test failed");
					}
					else
					{
						if (PRINTPASSES == true)
						{
							System.out.println("Test #7 Url: " + url + " test passed");
						}
					}

				}


			}


		}//End Test #7
		
		
		
		//Test #8: Invalid scheme with invalid authority and invalid path

		//Out loop for scheme
		for (int i = 0; i < numInvalidSchemes; i++)
		{
			//Middle loop for authority
			for (int j = 0; j < numInvalidAuthorities; j++)
			{
				//Inner loop for path
				for (int k = 0; k < numInvalidPaths; k++)
				{
					String url = "";
					url += invalidSchemes[i];
					url += invalidAuthorities[j];
					url += invalidPaths[k];

					//All of these tests should return false since the scheme, authority, and path are all invalid
					if (urlVal.isValid(url))
					{
						System.out.println("Test #8 Url: " + url + " test failed");
					}
					else
					{
						if (PRINTPASSES == true)
						{
							System.out.println("Test #8 Url: " + url + " test passed");
						}
					}

				}


			}


		}//End Test #8

   }
   
}
