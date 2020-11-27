#include "examples.h"
#include <string>
#include <iostream>
#include <istream>
#include <streambuf>
#include <sstream>
#include <fstream>


using namespace std;
using namespace seal;

int main(int argc, char *argv[] )
{


//cout << "********************** INSIDE SEAL SERVER ********************" << endl << endl << endl;

cout << " COMPUTATION using SEAL " << endl << endl << endl;


//file operations
//open file with ifstream variable cipherstring
//load file contents from en.txt file to ostringstream variable
//loading ostringstream contents to string variable
ifstream cipherstring("/tmp/en");

std::string temp;

if(cipherstring) {
   ostringstream streamt;
   streamt << cipherstring.rdbuf();
   temp = streamt.str();
}


//Generating context
    EncryptionParameters parms(scheme_type::bfv);
    size_t poly_modulus_degree = 4096;
    parms.set_poly_modulus_degree(poly_modulus_degree);
    parms.set_coeff_modulus(CoeffModulus::BFVDefault(poly_modulus_degree));
    parms.set_plain_modulus(1024);
    SEALContext context(parms);

//Load Evaluator with context
    Evaluator evaluator(context);

//Key Operations
//converting the received input ciphertext in string format to stringstream format
      std::istringstream streamsk(temp);

//create a Ciphertext variable and load with stringstream values
      Ciphertext yx_encrypted;
      yx_encrypted.load(context, streamsk);

//finding square of loaded ciphertext yx_encrypted
    Ciphertext yx_squared;
    evaluator.square(yx_encrypted, yx_squared);


//steps to write the square ciphertext to file
//1.convert ciphertext to stringstream
//2.load ciphertext contents in stringstream to string
//3.write to file

//ciphertext in binary format is saved to stream square
       std::stringstream square;
       yx_squared.save(square);
       std::string squaredcipher = square.str();

//writing contents of encrypted square value to temp file in /tmp folder
   std::ofstream out("/tmp/ensq");
   out << squaredcipher;
   out.close();


//cout << "****************END OF SEAL_SERVER***************** " << endl << endl << endl;

return 0;

}
