# Grades-Manager      
  The purpose of this program is to generate two output files, one with the student's classification mean
separated by disciplines in alphabetical order whilst the other has the student's who passed the year, in
alphabetic order. Passing the year equals passing at least 8 disciplines.</br></br>
  Requirements:</br>
  <ul>
    <li>The main project needs to receive a binary file as input  </li> 
      <li>Circular list(s) with priority(ies) with dynamic memory allocation </li> 
      <li>The output files need to be separated by \n </li> 
      <li>The name of the output files needs to be asked in the command prompt </li> 
  </ul>
      
 
  Project binaryFile - Creates binary file:</br>
       The program receives two text files, one with the students' name and number  and the other with the
   student's number, discipline, test and classification, each one of these separated by the same separator, ::.
  As example the first would have "name::number"  and  the second "number::discipline::test::classification".
  The name of both text files is asked for the user's input.</br>
       While reading each line of the files, if any incorrect data is found then it is discarded and the errors
   encountered are presented to the user indicating the line in which the error was found. If any information is
   discarded then the final output may be incorrect given the fact that that student may not be now registered in
   10 disciplines total.</br>
 
 CONTROLLED BEHAVIOURS:
       <ul>
         <li> If the user writes a file name that doesn't exist an error message is printed</li>
         <li> If the student isn't in the name number list it is not added to the final list</li>
         <li> If the numbers are negative, too large and not within range (0-20 for classifications and 0-4,294,967,295 for the students' number) then the information is discarded and not added to the final list</li>
         <li> If the files have less information that expected, e.g. name::text::classification, the information is discarded</li>
         <li> If there is only one test for the same discipline and person then test2 is filled as 0.0 and the mean is calculated</li>
        <li> If there is more than two tests to the same discipline and student the data is ignored</li> 
      </ul>

 </br>
 INDETERMINATE BEHAVIOURS:
        <ul>
         <li>If the user decides to use another separator rather than :: </li>
         <li>If the user gives the wrong .txt files</li>
       </ul>
 
</br></br>
  Project main - Creates two text output files:</br>
       The program receives a binary file which name is requested to the user. The binary file has the structures
   previously created in project 'binaryFile', we link its structures and then generate the first output file (the
   final classifications of individual separated by discipline). Then, the finalists structures are created,  which
   contain the names and number of disciplines that were passed by each individual and, to finish, we create the
   second output file where we only insert the names of the students that passed the respective number of subjects
   passed. It is assumed the binary name given in the Project binaryFile is the same as the one used in this program.</br>
   
  INDETERMINATE BEHAVIOURS:</br>
  <ul>
      <li>If the user writes the wrong extension to the name of the output files </li>
  </ul>
