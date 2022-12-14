
#include <iostream>
#include <boost/asio.hpp>
//#include <opencv4/opencv2/opencv.hpp>
//#include <opencv4/opencv2/core/utils/filesystem.hpp>


using namespace std;
/*#include <opencv4/opencv2/core.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>

#include <cassert>
#include <string>
#include <vector>

using namespace cv;*/


//Funcion que serializa la imagen, conviete el Matimagen a string serializado y viceverza
/*BOOST_SERIALIZATION_SPLIT_FREE( cv::Mat )

namespace boost {
    namespace serialization {

        template <class Archive>
        //Funcion que guarda los datos de la imagen
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
        //Funcion que carga los datos de la imagen para su uso posterior
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

//Funcion que convierte el Mat image a string serializado
std::string save( const cv::Mat & mat )
{
    std::ostringstream oss;
    boost::archive::text_oarchive toa( oss );
    toa << mat;

    return oss.str();
}

//Funcion que convierte el string serializado a Mat image
void load( cv::Mat & mat, const char * data_str )
{
    std::stringstream ss;
    ss << data_str;

    boost::archive::text_iarchive tia( ss );
    tia >> mat;
}

//Funcion que divide el Mat image en distintos objetos Mat
int divideImage(const cv::Mat& img, const int blockWidth, std::vector<cv::Mat>& blocks)
{
    // Comprueba si la imagen paso correctamente
    if (!img.data || img.empty())
    {
        std::cout << "Image Error: Cannot load image to divide." << std::endl;
        return EXIT_FAILURE;
    }

    // Dimensiones de la imagen
    int imgWidth = img.cols;
    int imgHeight = img.rows;
    std::cout << "IMAGE SIZE: " << "(" << imgWidth << "," << imgHeight << ")" << std::endl;

    // Dimenciones de los bloques (paginas)
    int bwSize;
    int bhSize = img.rows;

    //Dimencion de la imagen en bloques
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

//Funcion  que lee mensaje enviado por el servidor
string ReadMessage(boost::asio::ip::tcp::socket & socket) {
    boost::asio::streambuf buf; // Buffer de entrada de mensajes
    boost::asio::read_until( socket, buf, "\n"); //  Indica que lea mensaje del socket desde el buffer hasta el delimitador \n
    string data = boost::asio::buffer_cast<const char*>(buf.data()); // Hace cast del buffer de entrada a un char pointer (caracteres legibles)
    return data; // Retorna el mensaje recibido
}
//Funcion que envia mensaje al servidor
void SendMessage(boost::asio::ip::tcp::socket & socket, string message) {
    string msg = message + "\n"; // Declara variable string con un delimitador linea siguiente
    boost::asio::write( socket, boost::asio::buffer(msg)); // Envia mensaje a cliente mediante buffer
}*/


int main() {

    //Funcion main que implementa el algoritmo de paginacion
    /*cv::Mat image = imread("/home/alisson/Documentos/Proyecto1/Prueba.jpeg", IMREAD_COLOR);
    if (image.empty()) { //Verify if the image has been readed correctly
        cout << "Image File "
             << "Not Found" << endl;
        cin.get(); // wait for any key press
        return -1;
    }

    //Division de la imagen
    const int blockw = 50; //size of the blocks image that will be generated
    std::vector<cv::Mat> blocks; //vector that contains the blocks of image
    int divideStatus = divideImage(image, blockw, blocks); //divide image
    
    //Socket con implementacion de paginacion
    boost::asio::io_service io_service; //input/output service
    boost::asio::ip::tcp::socket socket(io_service); //declaration of sockets for conections

    socket.connect(boost::asio::ip::tcp::endpoint( boost::asio::ip::address::from_string("127.0.0.1"), 1234));
    cout << "Conectado al servidor" << endl;
    //string size = to_string(blocks.size());

    //Enviar el tama??o del vector en bloques
    //SendMessage(socket, size);
    SendMessage(socket, message);
    string receivedMessage = ReadMessage(socket);
    receivedMessage.pop_back();
    cout << "Server dice que: "<<receivedMessage<<endl;

    //Envia la imagen fuente
    /*for (int i = 0; i < blocks.size() ; i++){
        cv::Mat TEMP = blocks[i];
        std::string serialized = save(TEMP);
        SendMessage(socket, serialized);
        string receivedStatus = ReadMessage(socket);
        receivedStatus.pop_back();
        cout << "Server dice: "<<receivedStatus<<endl;
    }*/


    boost::asio::io_service io_service; // Servicio de input/output
    boost::asio::ip::tcp::socket socket(io_service); // Declaracion de socket para conexiones
    boost::system::error_code error; // Variable para codigo de error especifico de Boost
    boost::asio::streambuf receive_buffer; // Buffer para recibir mensajes
    const string outMessage = "Hola, soy el cliente\n"; // Mensaje a enviar

    socket.connect(boost::asio::ip::tcp::endpoint( boost::asio::ip::address::from_string("127.0.0.1"), 1234));
                                                                       // Conecta socket a IP local con puerto del servidor
    cout << "Conectado al servidor" << endl;

    boost::asio::write(socket, boost::asio::buffer(outMessage), error ); // Escribe mensaje al servidor

    if(!error) {
        cout << "Mensaje enviado" << endl;
    }
    else {
        cout << "error" << error.message() << endl;
    }

    boost::asio::read(socket, receive_buffer, boost::asio::transfer_all(), error); // Guarda mensaje recibido en el buffer

    if (error && error != boost::asio::error::eof) {
        cout << "error" << error.message() << endl;
    } else {
        const char* inMessage = boost::asio::buffer_cast<const char*>(receive_buffer.data()); // Interpreta mensaje recibido
        cout << "Servidor dice: " + (string) inMessage << endl; // Se hace cast a string al inMessage ya que es un const char pointer, para poder concatenarlo
    }
    return 0;
}