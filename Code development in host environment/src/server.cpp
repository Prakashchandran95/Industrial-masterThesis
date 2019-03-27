

#include "server.h"
#include "video.h"
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "communication/server_communication.h"

using namespace std;

 videomain rspi;
using namespace cv;
Mat resized_Mat;

void server()
{

    server_create(52000);
    cout << "Raspi Server is [on]" << endl;
    int key;


    while (1)
    {

        cout << "Waiting for the connection to Server ..." << endl;
        server_await_connection();
        cout << "Raspi Conected .. " << endl;

        bool ExitKey;
        ExitKey = false;



        while(1)
        {
            if(server_receive(&key, sizeof(int))!=0)
            { cout << "error: Blad przesylu danych" <<endl; }
            cout << "Got key " << key << endl;
            switch(key)
            {
            case 1: // full resolution photo

                server_send_photo(raspi.image);

                break;

            case 5551:

                resize(rspi.image, resized_Mat, Size(int(1920/2),int(1080/2)));
                server_send_photo(resized_Mat);
                break;

            case 9997:
                resize(rspi.image, resized_Mat, Size(1920/2,1080/2), 0, 0, INTER_LINEAR);
                server_send_photo(resized_Mat);
                break;

            case 9977:
                resize(rspi.image, resized_Mat, Size(1920/2,1080/2), 0, 0, INTER_LINEAR);
                server_send_photo(resized_Mat);
                break;

            case 9999: // Exit the communication
                ExitKey = true;
                break;
            }

            if (ExitKey == true)
                break;



        } // while Communication

        cout << " closing connection .. " << endl;

    } //while 1
} //while 1



