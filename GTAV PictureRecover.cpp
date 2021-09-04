#include <fstream>

int main(int argc, char* argv[])
{
	//Check if there is at least one picture to transform
	if (argc > 1)
	{
		//Loop for each files given as parameters
		for (int i = 1; i < argc; i++)
		{
			//Open the input file
			std::fstream input_file(argv[i], std::ios::binary | std::ios::in);

			if (input_file.is_open())
			{
				//Define the file output path
				char* output_path = new char[strlen(argv[i]) + 4];
				strcpy(output_path, argv[i]);
				strcat(output_path, ".jpg");

				//Open the output file
				std::fstream output_file(output_path, std::ios::binary | std::ios::out);

				if (output_file.is_open())
				{
					//Get the input file size
					input_file.seekg(0, std::ios::end);
					long file_size = input_file.tellg();

					//Remove the first 292 bytes from the file size as we won't copy them to the output
					file_size -= 292;

					//Set the reading cursor to 292 to skip the extra bytes added by GTA to the pictures
					input_file.seekg(292);

					//Read the bytes of the input file into a buffer
					unsigned char* buffer = new unsigned char[file_size];
					input_file.read((char*)buffer, file_size);

					//Copy the buffer to the output file
					output_file.write((char*) buffer, file_size);

					//Close the files
					input_file.close();
					output_file.close();

					//Free buffer
					delete[] buffer;
				}

				//Free buffer
				delete[] output_path;
			}
		}
	}
	else
	{
		printf("You need drag and drop the pictures' files on the exe to transform them.\n");
		system("PAUSE");
	}

	return 0;
}