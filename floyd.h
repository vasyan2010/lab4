//
// Created by admin on 20.05.2019.
//

#ifndef SETTINGUPGOOGLETESTS_FLOYD_H
#define SETTINGUPGOOGLETESTS_FLOYD_H
#include  <stdio.h>
#include  <windows.h>
#include  <conio.h>
#include  <stdlib.h>
#include  <ctype.h>
#include  <string.h>
#include  <iostream>
using namespace std;
const int NONE=-1;
const int maxSizeCityName=30;
const int startMatrixSize=2;
const int stepChangeMatrixSize=2;


class cities{
private:
    struct city
    {
        city *next;
        char name[maxSizeCityName];
        unsigned int nameSize;
    };

    city* cityHead;
    int ** matrix;
    unsigned int cityListSize;
    unsigned int matrixSize;
public:
    cities()
    {
        cityHead=NULL;

        matrix = new int*[startMatrixSize];
        for (unsigned int i = 0; i < startMatrixSize; i++)
        {
            matrix[i] = new int[startMatrixSize];
            for(unsigned int j = 0; j < startMatrixSize; j++)
                if (i!=j)
                    matrix[i][j]=NONE;
                else
                    matrix[i][j]=0;
        }
        cityListSize=0;
        matrixSize=startMatrixSize;
    };
    ~cities(){};


    int search(char * cityName, unsigned int nameSize)
    {
        city * search=cityHead;
        bool found=false;
        int numInList=cityListSize;
        while ((search!=NULL)&&(!found))
        {
            numInList--;
            if (nameSize==search->nameSize)
            {
                found=true;
                for (unsigned int i=0;(i<nameSize)&&(found);i++)
                    if(cityName[i]!=search->name[i])
                        found=false;
            }
            search=search->next;
        }
        return ((!found)?NONE:numInList);
    }

    void parser(char * str)
    {
        cout<<str;
        unsigned int nowPoint=0;

        /* 1*/
        int searchResult1;
        unsigned int city1NameSize;
        char city1Name[maxSizeCityName];
        for (city1NameSize=0;str[city1NameSize+nowPoint]!=';';city1NameSize++){};
        memcpy(city1Name, str+nowPoint, city1NameSize);
        city1Name[city1NameSize]='\0';
        searchResult1=search(city1Name,city1NameSize);
        if (searchResult1==NONE)
        {
            addNewCity(city1Name, city1NameSize);
            searchResult1=cityListSize-1;
        }
        nowPoint+=city1NameSize+1;

        /* 2 */
        int searchResult2;
        unsigned int city2NameSize;
        char city2Name[maxSizeCityName];
        for (city2NameSize=0;str[city2NameSize+nowPoint]!=';';city2NameSize++){};
        memcpy(city2Name, str+nowPoint, city2NameSize);
        city2Name[city2NameSize]='\0';
        searchResult2=search(city2Name,city2NameSize);
        if (searchResult2==NONE)
        {
            addNewCity(city2Name, city2NameSize);
            searchResult2=cityListSize-1;
        }
        nowPoint+=city2NameSize+1;


        if (str[nowPoint]=='N')
        {
            for (	;str[nowPoint]!=';';nowPoint++){};
            nowPoint++;
        }
        else
        {
            unsigned int cost12size;
            char cost12[11];
            for (cost12size=0;str[cost12size+nowPoint]!=';';cost12size++){};
            memcpy(cost12, str+nowPoint, cost12size);
            cost12[cost12size]='\0';
            matrix[searchResult1][searchResult2]=atoi(cost12);
            nowPoint+=cost12size+1;
        }

        if (str[nowPoint]!='N')
        {
            unsigned int cost21size;
            char cost21[11];
            for (cost21size=0;(str[cost21size+nowPoint]!='\0')&&(str[cost21size+nowPoint]!='\n');cost21size++){};
            memcpy(cost21, str+nowPoint, cost21size);
            cost21[cost21size]='\0';
            matrix[searchResult2][searchResult1]=atoi(cost21);;
        }
    }

    void addNewCity(char * cityName, unsigned int cityNameSize)
    {
        city * newCity=new city;
        newCity->next = cityHead;
        newCity->nameSize=cityNameSize;
        cityHead=newCity;
        memcpy(newCity->name, cityName, cityNameSize+1);
        cityListSize++;
        if (cityListSize>matrixSize)
        {
            unsigned int newMatrixSize=matrixSize+stepChangeMatrixSize;
            int **newMatrix =  new int*[newMatrixSize];
            for (unsigned int i = 0; i < newMatrixSize; i++)
                newMatrix[i] = new int[newMatrixSize];

            for (unsigned int i = 0; i < newMatrixSize; i++)
                for(unsigned int j = 0; j < newMatrixSize; j++)
                    if ((i>=matrixSize)||(j>=matrixSize))
                    {
                        if (i!=j)
                            newMatrix[i][j]=NONE;
                        else
                            newMatrix[i][j]=0;
                    }
                    else
                        newMatrix[i][j]=matrix[i][j];

            for (unsigned int i = 0; i < matrixSize; i++)
                delete [] matrix[i];
            delete[] matrix;
            matrixSize=newMatrixSize;
            matrix=newMatrix;
        }
    }

    void printCities()
    {
        cout<<"List of cities:\n";
        city * tmp = cityHead;

        for(unsigned int cityNum=cityListSize;tmp!=NULL;cityNum--)
        {
            cout<<cityNum;
            cout<<") "<<tmp->name<<endl;
            tmp=tmp->next;
        }
    }
    void printMatrix()
    {
        cout<<"Matrix:\n";
        for (unsigned int i = 0; i < matrixSize; i++)
        {
            for(unsigned int j = 0; j < matrixSize; j++)
            {
                if(matrix[i][j]==NONE)
                    cout<<" - ";
                else
                    printf("%3d",matrix[i][j]);
            }
            cout<<endl;
        }
    }
    int way(int i,int j)
    {
        if (i<cityListSize && j<cityListSize)
        {
            if(matrix[i][j]==NONE)
                cout<<"There is no such way"<<endl;
            else
            if (i!=j)
            {
                cout<<"Shortest distance:"<<matrix[i][j]<<endl;
                return matrix[i][j];
            }

            else
                cout<<"The same city is indicated, you are already at the destination."<<endl;
        }
        else
            cout<<"Input error (one or both numbers more than the number of cities)"<<endl;
        return -1;
    }
    void floudAlgoritm()
    {
        for (unsigned int k=0; k<matrixSize; k++)
            for (unsigned int i=0; i<matrixSize; i++)
                for (unsigned int j=0; j<matrixSize; j++)
                    if ((matrix[i][k] != NONE)&&(matrix[k][j] !=NONE))
                    {
                        if (matrix[i][j]==NONE)
                            matrix[i][j] = matrix[i][k] + matrix[k][j];
                        else
                            matrix[i][j] = min (matrix[i][j], matrix[i][k] + matrix[k][j]);
                    }
    }
};
#endif //SETTINGUPGOOGLETESTS_FLOYD_H
