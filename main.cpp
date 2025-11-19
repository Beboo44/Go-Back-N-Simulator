#include <iostream>
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;

#define MAX_PKT 20
#define MAX_SEQ 7

int window_size;
int frame_num;
typedef enum { FALSE , TRUE } boolean;
typedef unsigned int seq_nr;
typedef struct {unsigned char data[MAX_PKT];} packet;
typedef enum{data,ack,nak}frame_kind;


typedef struct{
    frame_kind kind;
    seq_nr seq;
    seq_nr ack;
    packet info;
} frame;

void print(packet p){
    for (int i = 0; i < MAX_PKT; i++) {
        cout<<p.data[i];
    }
}

int seq(int seq_n){

    if((rand()%100)<20){
        return rand()%MAX_SEQ;
    }
    else
        return seq_n;
}


int expected_frame = 0;

frame receiver(frame frame_received){
    frame s;
    if(frame_received.seq == expected_frame){
        s.ack = expected_frame;
        s.kind = ack;
        expected_frame = (expected_frame+1)%MAX_SEQ;
    }
    else{
        s.kind = nak;
    }
    return s;
}

void sender(vector<packet>&packets){
    seq_nr next_frame_to_send;
    seq_nr ack_expected;
    seq_nr frame_expected;
    frame r;

    ack_expected = 0;
    next_frame_to_send = 0;

    int size = packets.size();
    int window_begin = 0;
    bool flag = true;

    while(true){
        next_frame_to_send = ack_expected;
        flag = true;

        queue<pair<frame,int>>frames_to_be_sent;
        cout<<endl;
        cout<<"Sending Window: "<<endl;
        cout<<"==========================================="<<endl;
        for(int i = window_begin; i< min(window_begin+window_size,size); ++i){
            r.info = packets[i];
            r.seq = seq(next_frame_to_send);
            frames_to_be_sent.push({r,i});
            cout<<"Sender   : Frame " << i<<" is sent  Data_Sent: ";
            print(packets[i]);
            cout<<endl;
            next_frame_to_send = (next_frame_to_send+1)%MAX_SEQ;
        }
        cout<<"==========================================="<<endl;
        while(!frames_to_be_sent.empty()){
            frame received = receiver(frames_to_be_sent.front().first);


            if(received.kind==ack && received.ack==ack_expected){
                ack_expected = (ack_expected+1)%MAX_SEQ;
                ++window_begin;
                cout<<"Receiever: Frame "<<frames_to_be_sent.front().second<<" is received"<<endl;
            }
            else{
                flag = false;
                cout<<"!!!!! error has happened !!!!"<<endl;
                cout<<"Receiver: Frame "<<frames_to_be_sent.front().second<<" "<<"is lost. Send it again"<<endl;

                break;
            }
            frames_to_be_sent.pop();
        }
        cout<<"==========================================="<<endl;
        if(window_begin==size)
            break;
    }

}


int main() {

    srand(time(nullptr));

    cout<<"Please, Enter the window size -->";
    cin>>window_size;

    cout<<"Please, Enter number of data frames -->";
    cin>>frame_num;
    cout<<"-----------------------------------------"<<endl;
    cout<<endl;


    cout<<"Go-Back-N Protocol"<<endl;

    cout<<"Window Size: " << window_size<<endl;
    cout<<endl;
    cout<<"-----------------------------------------"<<endl;



    vector<packet>packets(frame_num);
    for (auto &p : packets) {
        for (int i = 0; i < MAX_PKT; i++) {
            p.data[i] = rand() % 26 + 'a';
        }
    }
    sender(packets);


    return 0;
}