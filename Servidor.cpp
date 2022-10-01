#include <iostream>
#include <boost/asio.hpp> // Incluir libreria de Boost Asio

/*#include <fstream>

#include <opencv4/opencv2/opencv.hpp>
#include <opencv4/opencv2/core/utils/filesystem.hpp>
#include <opencv4/opencv2/core.hpp>
#include <boost/serialization/split_free.hpp>
#include <opencv4/opencv2/opencv_modules.hpp>

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

#include "opencv4/opencv2/imgcodecs.hpp"
#include "opencv4/opencv2/highgui.hpp"
#include "opencv4/opencv2/stitching.hpp"

#include <string>
#include <utility>
#include <vector>*/

using namespace std;
//using namespace cv;

/*

int divideImage(const cv::Mat& img, const int blockWidth, std::vector<cv::Mat>& blocks){
    // Checking if the image was passed correctly
    if (!img.data || img.empty())
    {
        std::cout << "Image Error: Cannot load image to divide." << std::endl;
        return EXIT_FAILURE;
    }

    // init image dimensions
    int imgWidth = img.cols;
    int imgHeight = img.rows;
    std::cout << "IMAGE SIZE: " << "(" << imgWidth << "," << imgHeight << ")" << std::endl;

    // init block dimensions
    int bwSize;
    int bhSize = img.rows;

    int y0 = 0;
    int x0 = 0;
    while (x0 < imgWidth)
    {
        bwSize = ((x0 + blockWidth) > imgWidth) * (blockWidth - (x0 + blockWidth - imgWidth)) + ((x0 + blockWidth) <= imgWidth) * blockWidth;

        blocks.push_back(img(cv::Rect(x0, y0, bwSize, bhSize)).clone());

        x0 = x0 + blockWidth;

    }
    return EXIT_SUCCESS;
}


 //function that serialize the image, convert the Mat image to serialized string and viceversa

BOOST_SERIALIZATION_SPLIT_FREE( cv::Mat )

namespace boost {
    namespace serialization {
        template <class Archive>
        void save( Archive & ar, const cv::Mat & m, const unsigned int version )
        {
            size_t elemSize = m.elemSize();
            size_t elemType = m.type();

            ar & m.cols;
            ar & m.rows;
            ar & elemSize;
            ar & elemType;

            const size_t dataSize = m.cols * m.rows * m.elemSize();
            for ( size_t i = 0; i < dataSize; ++i )
                ar & m.data[ i ];
        }
        template <class Archive>
        void load( Archive & ar, cv::Mat& m, const unsigned int version )
        {
            int cols, rows;
            size_t elemSize, elemType;

            ar & cols;
            ar & rows;
            ar & elemSize;
            ar & elemType;

            m.create( rows, cols, static_cast< int >( elemType ) );
            const size_t dataSize = m.cols * m.rows * elemSize;
            for (size_t i = 0; i < dataSize; ++i)
                ar & m.data[ i ];
        }
    }
}


std::string save( const cv::Mat & mat )
{
    std::ostringstream oss;
    boost::archive::text_oarchive toa( oss );
    toa << mat;

    return oss.str();
}



void load( cv::Mat & mat, const char * data_str )
{
    std::stringstream ss;
    ss << data_str;

    boost::archive::text_iarchive tia( ss );
    tia >> mat;
}
*/



string ReadMessage(boost::asio::ip::tcp::socket & socket) {
    boost::asio::streambuf buf;
    boost::asio::read_until( socket, buf, "\n" );
    string data = boost::asio::buffer_cast<const char*>(buf.data());
    return data;
}

void SendMessage(boost::asio::ip::tcp::socket & socket, string message) {
    string msg = message + "\n";
    boost::asio::write( socket, boost::asio::buffer(msg));
}


    /*int main() {
    boost::asio::io_service io_service; //input/output service
    boost::asio::ip::tcp::acceptor acceptor_(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(),1234));
    boost::asio::ip::tcp::socket socket_(io_service); //declaration of socket

    cout << "Servidor iniciado" << endl;
    acceptor_.accept(socket_);
    cout << "Cliente conectado" << endl;

    string sizeMessage = ReadMessage(socket_);
    sizeMessage.pop_back(); // Popping last character "\n"
    SendMessage(socket_, "Tamaño recibido");
    int size = stoi(sizeMessage);

    vector<cv::Mat> blocks;
    //receiving the image source
    
    for (int i = 0; i < size; i++) {
        string message = ReadMessage(socket_); // Lee y declara mensaje del cliente
        SendMessage(socket_, "Pedazo " + to_string(i) + " recibido");
        message.pop_back();
        Mat result;
        load(result, message.c_str());
        blocks.push_back(result);
    }
//Funcion que lee mensaje enviado por cliente

string ReadMessage(boost::asio::ip::tcp::socket & socket) 
    {
    boost::asio::streambuf buf; // Buffer de entrada de mensajes
    boost::asio::read_until( socket, buf, "\n" ); //  Indica que lea mensaje del socket desde el buffer hasta el delimitador \n
    string data = boost::asio::buffer_cast<const char*>(buf.data()); // Hace cast del buffer de entrada a un char pointer (caracteres legibles)
    return data; // Retorna el mensaje recibido
    }

//Funcion que envia mensaje al cliente

void SendMessage(boost::asio::ip::tcp::socket & socket, const string& message) {
    const string msg = message + "\n"; // Declara variable string con un delimitador linea siguiente
    boost::asio::write( socket, boost::asio::buffer(message)); // Envia mensaje a cliente mediante buffer
}*/

int main() {
    boost::asio::io_service io_service; // Servicio de input/output
    boost::asio::ip::tcp::acceptor acceptor_(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 1234));
                                            // Acepta de manera asincrona conexiones en puerto 1234
    boost::asio::ip::tcp::socket socket_(io_service); // Declaracion de socket para conexiones

    cout << "Servidor iniciado" << endl;

    acceptor_.accept(socket_); // Acepta al socket del cliente que pida conectarse

    cout << "Cliente conectado" << endl;

    string message = ReadMessage(socket_); // Lee y declara mensaje del cliente
    cout << "Cliente dice: " + message << endl;

    SendMessage(socket_, "Hola, soy el servidor"); // Envia mensaje al cliente
    cout << "Mensaje enviado" << endl;
    return 0;
}