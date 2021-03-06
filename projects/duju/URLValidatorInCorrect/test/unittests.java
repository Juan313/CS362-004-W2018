//Alexander Gilmour
//UrlValidatorRandTest.java
//CS 362 Extra Credit
//3-13-18


import java.util.Random;
import junit.framework.TestCase;

class Unittests{
	public static void main(String[] args) {	


		UrlValidator urlVal = new UrlValidator();
		
		//Default is to not print output from passing tests because we are only concerned with failures
		boolean PRINTPASSES = false;

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



















	}// End main




} // End Class

