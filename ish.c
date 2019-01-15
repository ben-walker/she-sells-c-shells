const char *mypath[] = { "./",
"/usr/bin/", "/bin/", NULL
};

/* Parse input */
while (( ... = strsep (...)) != NULL)
{
...
}

/* If necessary locate executable using mypath array */

/* Launch executable */
if (fork () == 0) {
 
} else {

} // end of if

}
