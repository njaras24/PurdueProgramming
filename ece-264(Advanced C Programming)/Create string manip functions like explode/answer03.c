#include "answer03.h"
#include<string.h>
#include<stdlib.h>
#include<malloc.h>

/**
 * Append the C-string 'src' to the end of the C-string '*dest'.
 *
 * strcat_ex(...) will append the C-string 'src' to the end of the string
 * at '*dest'. The parameter 'n' is the address of a int that specifies how
 * many characters can safely be stored in '*dest'. 
 *
 * If '*dest' is NULL, or if '*dest' is not large enough to contain the result
 * (that is, the sum of the lengths of *dest, src, and the null byte), then
 * strcat_ex will:
 * (1) malloc a new buffer of size 1 + 2 * (strlen(*dest) + strlen(src))
 * (2) set '*n' to the size of the new buffer
 * (3) copy '*dest' into the beginning of the new buffer
 * (4) free the memory '*dest', and then set '*dest' to point to the new buffer
 * (5) concatenate 'src' onto the end of '*dest'.
 *
 * Always returns *dest.
 *
 * Why do we need to pass dest as char * *, and n as int *? 
 * Please see the FAQ for an answer.
 *
 * Hint: These <string.h> functions will help: strcat, strcpy, strlen.
 * Hint: Leak no memory.
 */
char * strcat_ex(char * * dest, int * n, const char * src )
{
  char * buffer; //        To store cat string
  if ( ( ( * dest ) == NULL ) || ( strlen ( *dest ) + strlen ( src ) > *n ) )
    {
      if ( * dest != NULL )
	{
	  buffer = malloc ( 1 + 2 * ( strlen ( *dest ) + strlen ( src ) ) );
	  *n = ( 1 + 2 * ( strlen ( *dest ) + strlen ( src ) ) );
	  buffer[0] ='\0';
	  strcpy ( buffer, *dest );
	  free ( *dest );
	  *dest = buffer;
	}
      else if ( * dest == NULL )
	{
	  buffer = malloc ( 1 + 2 * ( strlen ( src ) ) );
	  *n = ( 1 + 2 * strlen ( src ) );
	  buffer[0] ='\0';
          free ( *dest );
          *dest = buffer;
	}
    }
  strcat ( *dest, src );
  return *dest;
}



/**
 * Takes a string and splits it into an array of strings according to delimiter.
 * The memory location '*arrLen' is initialized to the length of the returned
 * array.
 *
 * str: A string to split
 * delims: a string that contains a set of delimiter characters. explode(...) 
 *         will split the string at any character that appears in 'delims'.
 * arrLen: pointer to an int that is used to store the resultant length of the
 *         returned array.
 *
 * For example, if delimiter is white space " \t\v\n\r\f", then,
 * int len;
 * char * * strArr = explode("The\nTuring test", " \t\v\n\r\f", &len);
 * // len = 3, strArr[0] is "The", strArr[1] is "Turing", strArr[2] is "test"
 *
 * Hint: you can use <string.h> functions "memcpy" and "strchr"
 *       "memcpy" copies blocks of memory.
 *       "strchr" can be used to tell if a specific character is in delims.
 * Hint: this question is hard; it will help to draw out your algorithm.
 * Hint: read the FAQ...
 */
char * * explode(const char * str, const char * delims, int * arrLen)
{

  int N=0;//number of delimiters in str
  
  int last = 0; // 1 + the last index we saw a delimiter. Init to 0.
  int ind=0; //loop control variable or the variable that we are currently viewing
  int arrInd = 0; // this is the next position where we'll create a string

  int str_len; //length of str
  str_len= strlen(str);
  
  for(ind=0;ind<str_len;ind++)
    {
      if(strchr(delims,str[ind]) != NULL)
		N++;
    }
  
  char * * strArr = malloc((N+1) * sizeof(char *));

  for(ind=0;ind<str_len;ind++)
    {
	  if (strchr(delims, str[ind]) != NULL)
	  {
		  strArr[arrInd] = malloc((ind - last + 1)*sizeof(char));//ask why you have to use malloc again
		  
		  memcpy(strArr[arrInd], str + last, ind-last);
		  strArr[arrInd][ind-last] = '\0';

		 last = ind + 1;
		 arrInd++;
	  }
	}
  

  strArr[N]=malloc(ind-last+1);//ask why you have to use malloc again 
  memcpy(strArr[arrInd], str + last, ind - last);
  strArr[N][ind-last]='\0';

  *arrLen=N+1;
  return strArr;

}

/**
 * Takes an array of strings, and concatenates the elements into a single
 * string, placing 'glue' between each successive element.
 *
 * strArr: an array of strings
 * len: the length of the array 'strArr'
 * glue: string to concatenate between each element of 'strArr'
 *
 * For example:
 * int len;
 * char * * strArr = explode("100 224 147 80", " ", &len);
 * char * str = implode(strArr, len, ", ");
 * printf("(%s)\n", str); // (100, 224, 147, 80)
 *
 * Hint: use strcat_ex in a for loop.
 */
char * implode(char * * strArr, int len, const char * glue)
{
  int i=0;
  int n=0;
  int glue_len=0;
  char* str=malloc(1*sizeof(char));//final string formed after gluing different strings
  /*str=strArr[0];//str="the" */
  /* for(i=0;i<len;i++) */
  /*   { */
  /*     n=n+strlen(strArr[i]); */
  /*   }  */
  str[0]='\0';
  for(i=0;i<len;i++)
    {
      strcat_ex(&str,&n,strArr[i]);
      if(i<len-1)
	{
          strcat_ex(&str,&glue_len,glue);
	}
    }

  return str;
}


  //for(i=1;i<len;i++)
  /*     strcat(strArr[i],glue);
    }
  char* buffer=malloc(n*sizeof(char));
  for(i=1;i<len-1;i++)
    {
    memcpy(buffer,strArr[i],*/

/**
 * Takes an array of C-strings, and sorts them alphabetically, ascending.
 *
 * arrString: an array of strings
 * len: length of the array 'arrString'
 *
 * For example, 
 * int len;
 * char * * strArr = explode("lady beatle brew", " ", &len);
 * sortStringArray(strArr, len);
 * char * str = implode(strArr, len, " ");
 * printf("%s\n"); // beatle brew lady
 *
 * Hint: use the <stdlib.h> function "qsort"
 * Hint: you must _clearly_ understand the typecasts.
 */

//This is the function for comparing strings.

int cstring_cmp(const void *a, const void *b)
{
  const char **ia = (const char **)a;
  const char **ib = (const char **)b;
  return strcmp(*ia, *ib);
  /* strcmp functions works exactly as expected from
     comparison function */
}

int string_cmp(const void *a, const void *b)
{
  const char *ia = (const char *)a;
  const char *ib = (const char *)b;
  char a1= *ia;
  char b1= *ib;
  if((int)a1<(int)b1){return -1;}
  if((int)a1==(int)b1){return 0;}
  return 1;
}

void sortStringArray(char * * arrString, int len)
{
  //char* str;//string sorted in ascending order alphabetically
  qsort(arrString,len ,sizeof(char *) ,cstring_cmp);
}
/**
 * Sorts the characters in a string.
 *
 * str: string whose characters are to be sorted
 *
 * For example, 
 * char * s1 = strdup("How did it get so late so soon?");
 * sortStringCharacters(s1)
 * // s1 is now "       ?Haddeegiilnooooossstttw"
 *
 * Hint: use the <stdlib.h> function "qsort"
 * Hint: you must _clearly_  understand the typecasts.
 */
void sortStringCharacters(char * str)
{
  int len = strlen(str);//length of the string
  qsort(str,len ,sizeof(char) ,string_cmp);
}


/**
 * Safely frees all memory associated with strArr, and then strArr itself.
 * Passing NULL as the first parameter has no effect.
 *
 * strArr: an array of strings
 * len: the length of 'strArr'
 *
 * int len;
 * const char * abe = "Give me six hours to chop down a tree and I will spend\n"
 *                    "the first four sharpening the axe.";
 * char * * strArr = explode(abe, "\n ");
 * destroyStringArray(strArr, len); // cleans memory -- no memory leaks
 * destroyStringArray(NULL, 0); // does nothing, does not crash.
 */
void destroyStringArray(char * * strArr, int len)
{
  int i=0;
  /* if(strArr!=NULL) */
  /*  { */
     for(i=0;i<len;i++)
       {
	 free(strArr[i]);
       }
     free(strArr);
     // }
}


