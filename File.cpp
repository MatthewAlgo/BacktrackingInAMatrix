/*
Copyright (c) 2021 MatthewAlgo

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/



#include <iostream>
#include <iomanip>
#include <fstream>
#include <array>
#include <vector>
#include <ios>
#include <optional>
#include <functional>
#include <deque>
#include <queue>
#include <thread>
#include <string>
#include <cstring>
#include <random>
#include <stdio.h>      /* printf, fgets */
#include <stdlib.h>    /* atoi */

// SFML Additions
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

// #include "Algorithms.hpp"

// For Threads
#include <X11/Xlib.h>
#define DEBUG

namespace MatthewsNamespace
{

    template <typename Type_of_function>
    void Runfunction(void (*pfunc)(Type_of_function ARG)) // Run a function that takes one argument
    {
        Type_of_function ARG;
        pfunc(ARG);
    }
    // Pseudo-random generator
    template <typename TYPE>
    TYPE RAND(TYPE lower, TYPE upper)
    {
        std::random_device random_device;
        std::mt19937 random_engine(random_device());
        std::uniform_int_distribution<int> distribution_1_1000(lower, upper);

        TYPE randomNumber = distribution_1_1000(random_engine);

        return static_cast<TYPE>(randomNumber);
    }
    class MatthewStaticVariables
    {
    protected:
        // Files
        inline static std::fstream *FILEINPUT = new std::fstream("MATRIXTEST.json", std::ios::in);
        inline static std::fstream *FILEFOROUTPUT_PF = new std::fstream("PATHFIND/POSSIBLE_WAYS.json", std::ios::out);
        // Variables
        static constexpr int MaxNoOfLines = std::numeric_limits<int16_t>::max(); 
        inline static std::array<std::array<int, 100>, 100> *MatrixArray = new std::array<std::array<int, 100>, 100>();
        inline static std::vector<std::vector<int>> *MatrixInitial = new std::vector<std::vector<int>>();
        inline static std::vector<std::vector<int>> *MatrixForJ = new std::vector<std::vector<int>>(); // Gets filled only from input at the beginning
        inline static std::vector<std::vector<int>> *MatrixForR = new std::vector<std::vector<int>>(); // Gets filled only from input at the beginning
        inline static std::vector<std::vector<int>> *CopyMatrix = new std::vector<std::vector<int>>(); // Gets filled only from input and stays like that
        inline static std::vector<sf::Vector2f>* LINES = new std::vector<sf::Vector2f>();
        inline static int64_t CurrentPositionInVertexArray = -1;
        inline static std::vector<sf::Vector2f>* COLUMNS = new std::vector<sf::Vector2f>();
        inline static sf::Vertex* VertexofLines = new sf::Vertex[MaxNoOfLines];
        inline static std::vector<sf::RectangleShape>* WALLS_IN_MATRIX =new std::vector<sf::RectangleShape>();
        inline static std::vector<sf::RectangleShape>* COLORED_IN_MARIX = new std::vector<sf::RectangleShape>();
        inline static std::vector<std::vector<sf::RectangleShape>>* VectorOfPossibleMatrices = new std::vector<std::vector<sf::RectangleShape>>();
        inline static std::vector<std::vector<sf::Text>>* VectorOfTextForMatrices = new std::vector<std::vector<sf::Text>>();
        inline static constexpr int WALL = -1;
        inline static bool RJ_H = false, RJ_S = false, PATH = false, OKSTART = false;
        inline static size_t lines, columns;
        inline static double DISPLACEMENT_COLS, DISPLACEMENT_LINES;
        struct DATA_STRUCTURE
        {
            size_t xpos, ypos;
            size_t value;
            DATA_STRUCTURE() = default;
            ~DATA_STRUCTURE() = default;
        };

    public: // Constructor-destructor
        MatthewStaticVariables() = default;
        ~MatthewStaticVariables();
    public: // Getters and Accessors for static vars

        // Getters For Copy Matrix, Romeo Matrix and Julieta Matrix
        static bool* getRJ_H(){
            return &RJ_H;
        }
        static bool* getOKSTART(){
            return &OKSTART;
        }
        static bool* getRJ_S(){
            return &RJ_S;
        }
        static bool* getPATH(){
            return &PATH;
        }
        static std::vector<std::vector<int>>* getRomeoMatrix() noexcept{
            return MatrixForR;
        }
        static std::vector<std::vector<int>>* getJulietaMatrix() noexcept{
            return MatrixForJ;
        }
        static std::vector<std::vector<int>>* getCopyMatrix() noexcept {
            return CopyMatrix;
        }
        // Other getters 
        static double* getDISPLACEMENT_COLS(){
            return &DISPLACEMENT_COLS;
        }
        static double* getDISPLACEMENT_LINES(){
            return &DISPLACEMENT_LINES;
        }
        static std::vector<sf::Vector2f>* GetLINESDirectly(){
            return LINES;
        }
        static std::vector<sf::Vector2f>* GetColumnsDirectly(){
            return COLUMNS;
        }
        static sf::Vertex* getVertexofLines(){
            return VertexofLines;
        }
        static int64_t* getVertexArrSize(){
            return &CurrentPositionInVertexArray;
        }
        static std::vector<std::vector<int>> *getTheInitialisedMatrix(){
            return MatrixInitial;
        }
        static std::vector<sf::RectangleShape>* getColoredInMatrix(){
            return COLORED_IN_MARIX;
        }
        static std::fstream *getInFileWithMatrix(){
            return FILEINPUT;
        }
        static std::fstream* getOutFileForPathFind(){
            return FILEFOROUTPUT_PF;
        }
        static std::vector<sf::RectangleShape>* getWallsInMatrix(){
            return WALLS_IN_MATRIX;
        }
        static void PRINT_MATRIX(std::ostream &OUTPUT, std::vector<std::vector<int>> &REFERENCED)
        {
            printf("~~Printing matrix~~\n");
            for (std::vector<std::vector<int>>::iterator it = REFERENCED.begin();
                 it != REFERENCED.end(); ++it)
            {
                for (std::vector<int>::iterator itersecond = it->begin(); itersecond != it->end(); ++itersecond)
                {
                    OUTPUT << std::setw(4) << *itersecond << " ";
                }
                OUTPUT << std::endl;
            }
        }
        static std::vector<std::vector<sf::RectangleShape>>* getVectorOfPossibleMatrices(){
            return VectorOfPossibleMatrices;
        }
        static std::vector<std::vector<sf::Text>>* getVectorOfTexts(){
            return VectorOfTextForMatrices;
        }

    };
    struct MatrixWindow{ // Using the SFML Library
        private:
        sf::RenderWindow* Window; // See if we can use smart pointers here
        inline static int32_t WindowLength = 600, WindowWidth = 600;
        sf::Thread* ThreadForWindow;
        static inline sf::Mutex* MUTEX = new sf::Mutex();
        static inline int iposPATH =0 , jposPATH =0;
        inline static std::vector<sf::Vector2f> VectorOfLines{};
        static inline int CurrentFrameForColored = 0; 
        public: // Constructors
        #if defined (DEBUG)
        // ~~And a square drawing algorithm~~
        void DrawTheInitSquare(int ipos, int jpos, sf::RenderWindow* w){
            sf::RectangleShape Rect;
            Rect.setFillColor(sf::Color::Black);
            Rect.setPosition(sf::Vector2f(*MatthewStaticVariables::getDISPLACEMENT_COLS()/2 -*MatthewStaticVariables::getDISPLACEMENT_COLS()/2 + (ipos-1<0?0:ipos)**MatthewStaticVariables::getDISPLACEMENT_COLS(), *MatthewStaticVariables::getDISPLACEMENT_LINES()/2 -*MatthewStaticVariables::getDISPLACEMENT_COLS()/2 + (jpos-1 < 0 ? 0:jpos)**MatthewStaticVariables::getDISPLACEMENT_LINES()));
            Rect.setSize(sf::Vector2f(*MatthewStaticVariables::getDISPLACEMENT_COLS(), *MatthewStaticVariables::getDISPLACEMENT_LINES()));
            w->draw(Rect);
        }
        MatrixWindow() : Window{new sf::RenderWindow(sf::VideoMode(static_cast<int32_t>(WindowLength),static_cast<int32_t>(WindowWidth)), "PlayGround")}, ThreadForWindow{
            new sf::Thread{[&](MatthewsNamespace::MatrixWindow* w){
                sf::Context context; bool IS_ACTIVE = false;
                // Build the array of lines
                // MatthewsNamespace::MatthewsObjectStatic::BuildTheMatrixGRAPH(); -> In the matrix initialization
                printf("Drawing at length %i and width %i", *MatrixWindow::getLength(), *MatrixWindow::getWidth());
                w->getRenderWindow()->setActive(true);
                while(w->getRenderWindow()->isOpen()){
                    sf::Event SFML_EVENT;
                    while(w->getRenderWindow()->pollEvent(SFML_EVENT)){
                        // Creates an event
                        if(SFML_EVENT.type == sf::Event::Closed){
                            w->getRenderWindow()->close();
                        }
                        if(SFML_EVENT.type == sf::Event::MouseButtonReleased){
                            CurrentFrameForColored++;
                        }
                    }
                    MUTEX->lock();
                    w->getRenderWindow()->clear(sf::Color::Yellow);
                    this->DrawInWindow();
                    DrawTheInitSquare(iposPATH, jposPATH, this->getRenderWindow());
                    w->getRenderWindow()->draw(MatthewStaticVariables::getVertexofLines(), *MatthewStaticVariables::getVertexArrSize()+1, sf::Lines);
                    // Function to draw the current list of colored squares
                    if(*MatthewStaticVariables::getPATH() == true){
                        if(*MatthewStaticVariables::getOKSTART() == true){
                        if(MatthewStaticVariables::getVectorOfPossibleMatrices()->size()>CurrentFrameForColored){
                            // Draw squares at MatthewStaticVariables::getVectorOfPossibleMatrices()->at(CurrentFrameForColored)
                            for(size_t i{}; i<MatthewStaticVariables::getVectorOfPossibleMatrices()->at(CurrentFrameForColored).size(); ++i){
                                w->getRenderWindow()->draw(MatthewStaticVariables::getVectorOfPossibleMatrices()->at(CurrentFrameForColored).at(i));
                            }
                            // Draw texts at MatthewStaticVariables::getVectorOfTexts()->at(CurrentFrameForColored)
                            for(size_t i{}; i<MatthewStaticVariables::getVectorOfTexts()->at(CurrentFrameForColored).size(); ++i){
                                sf::Font Fnt;
                                Fnt.loadFromFile("FONTS/RMONO.ttf"); 
                                MatthewStaticVariables::getVectorOfTexts()->at(CurrentFrameForColored).at(i).setFont(Fnt);
                                w->getRenderWindow()->draw(MatthewStaticVariables::getVectorOfTexts()->at(CurrentFrameForColored).at(i));
                            }
                        }else{
                            if(IS_ACTIVE == false){
                                printf("\nEnd of possibilities generation. Ending.\n");
                                printf("The main window is now inactive\n");
                                IS_ACTIVE = true;
                            }
                            // w->getRenderWindow()->close();
                        }
                        }
                    }
                    if(*MatthewStaticVariables::getRJ_H() == true){
                        /// For Romeo and Julieta-Heap
                    }
                    w->getRenderWindow()->display();
                    MUTEX->unlock();
                }
            }, this}
        }{
            ThreadForWindow->launch();  
        };
        #elif not defined (DEBUG)
        MatrixWindow() {
            // Init the window 
            this->Window = new sf::RenderWindow(sf::VideoMode(static_cast<int32_t>(WindowLength),static_cast<int32_t>(WindowWidth)), "PlayGround");
            this->ThreadForWindow = new sf::Thread(&MatthewsNamespace::MatrixWindow::FUNCTOR_FOR_WINDOW, this);
            this->ThreadForWindow->launch();

        }
        void FUNCTOR_FOR_WINDOW(){
            auto FunctionToExecute = [&](MatthewsNamespace::MatrixWindow* w){
                sf::Context context;
                w->getRenderWindow()->setActive(true);
                while(w->getRenderWindow()->isOpen()){
                    sf::Event SFML_EVENT;
                    while(w->getRenderWindow()->pollEvent(SFML_EVENT)){
                        // Creates an event
                        if(SFML_EVENT.type == sf::Event::Closed){
                            w->getRenderWindow()->close();
                        }
                    }
                    w->getRenderWindow()->clear(sf::Color::Yellow);
                    w->getRenderWindow()->display();
                }
            };
            FunctionToExecute(this);
        }
        #endif
        ~MatrixWindow(){}

        public: // Getters
        static int32_t* getLength() noexcept{
            return &WindowLength;
        }
        static int* getiposPATH(){
            return &iposPATH;
        }
        static int* getjposPATH(){
            return &jposPATH;
        }
        static int32_t* getWidth() noexcept{
            return &WindowWidth;
        }
        sf::RenderWindow* getRenderWindow() noexcept{
            return Window;
        }
        sf::RenderWindow& getRenderWindowReference() noexcept{
            return *Window;
        }
        sf::Thread* getThread() noexcept {
            return ThreadForWindow;
        }
        static sf::Mutex* getMutex() noexcept{
            return MUTEX;
        }

        public: // Setters
        static void setLength(int32_t VALUE){
            WindowLength = VALUE;
        }
        static void setWidth(int32_t VALUE){
            WindowWidth = VALUE;
        }

        public: // Different functions
        static std::vector<sf::Vector2f>* getCOLUMNSFromGL(){
            return MatthewsNamespace::MatthewStaticVariables::GetColumnsDirectly();
        }
        static std::vector<sf::Vector2f>* getLINESFromGL(){
            return MatthewsNamespace::MatthewStaticVariables::GetLINESDirectly();
        }

        void DrawInWindow(){
            sf::VertexArray VertArrayLines;
            for(std::vector<sf::Vector2f>::iterator it=getLINESFromGL()->begin(); it !=getLINESFromGL()->end(); ++it){
                VertArrayLines.append(sf::Vertex(sf::Vector2f(*it), sf::Color::Blue));
            }
            // Draw the lines
            this->getRenderWindow()->draw(VertArrayLines);
            sf::VertexArray VertArrayColumns;
            for(std::vector<sf::Vector2f>::iterator it=getCOLUMNSFromGL()->begin(); it !=getCOLUMNSFromGL()->end(); ++it){
                VertArrayLines.append(sf::Vertex(sf::Vector2f(*it), sf::Color::Blue));
            }
            this->getRenderWindow()->draw(VertArrayColumns);
            // Draw the walls
            for(std::vector<sf::RectangleShape>::iterator it = MatthewStaticVariables::getWallsInMatrix()->begin(); it != MatthewStaticVariables::getWallsInMatrix()->end(); ++it){
                this->getRenderWindow()->draw(*it);
            }
        }

    };
    class MatthewsObjectStatic : MatthewStaticVariables
    {
    public:
        // Diverse Functions and getters / setters
        std::array<std::array<int, 100>, 100> getArray()
        {
            return *MatthewStaticVariables::MatrixArray;
        }
        static void ShowMatrix(std::ostream &OUTPUT, std::vector<std::vector<int>> &REFERENCED)
        {
            for (std::vector<std::vector<int>>::iterator it = REFERENCED.begin();
                 it != REFERENCED.end(); ++it)
            {
                for (std::vector<int>::iterator itersecond = it->begin(); itersecond != it->end(); ++itersecond)
                {
                    OUTPUT << std::setw(4) << *itersecond << " ";
                }
                OUTPUT << std::endl;
            }
        }
        static void ResetAllMatrices(){
            // All will receive the value of CopyMatrix
            for(int i{};i<MatthewsNamespace::MatthewStaticVariables::lines-1;++i){
                for(int j{};j<MatthewsNamespace::MatthewStaticVariables::lines-1;++j){
                    MatthewsNamespace::MatthewStaticVariables::getRomeoMatrix()->at(i).at(j) = MatthewStaticVariables::getCopyMatrix()->at(i).at(j);
                    MatthewStaticVariables::getJulietaMatrix()->at(i).at(j) = MatthewStaticVariables::getCopyMatrix()->at(i).at(j);
                    MatthewStaticVariables::getTheInitialisedMatrix()->at(i).at(j) = MatthewStaticVariables::getCopyMatrix()->at(i).at(j);
                }
            }

        }
        static void IninialiseMatrixFromInput(std::istream &INPUT, std::vector<std::vector<int>> &REFERENCED)
        {
            //Reading Our Matrix From file
            std::cout << "\nFILLING BUFFERS...\n";
            REFERENCED.clear();
            MatthewsNamespace::MatthewStaticVariables::CopyMatrix->clear(); // Also fill the initial matrix
            MatthewsNamespace::MatthewStaticVariables::MatrixForJ->clear();
            MatthewsNamespace::MatthewStaticVariables::MatrixForR->clear();
            INPUT >> MatthewStaticVariables::lines >> MatthewStaticVariables::columns;
            std::cout << "SIZE OF MATRIX: " << MatthewStaticVariables::lines << " / " << MatthewStaticVariables::columns << "\n";
            for (size_t i{}; i < MatthewStaticVariables::lines; ++i)
            {
                const size_t LITERAL = MatthewStaticVariables::lines;
                REFERENCED.push_back(std::vector<int>{});
                MatthewsNamespace::MatthewStaticVariables::CopyMatrix->push_back(std::vector<int>{});
                MatthewsNamespace::MatthewStaticVariables::MatrixForJ->push_back(std::vector<int>{});
                MatthewsNamespace::MatthewStaticVariables::MatrixForR->push_back(std::vector<int>{});
                for (size_t j{}; j < MatthewStaticVariables::columns; ++j)
                {
                    int CurrentElement;
                    INPUT >> CurrentElement;
                    try
                    {
                        switch (CurrentElement)
                        {
                        default:
                            if (CurrentElement != 0 && CurrentElement != -1)
                            {
                                throw std::pair<int,std::string>(404, "The matrix configuration is not valid!"); 
                            }
                        }
                        REFERENCED.at(i).push_back(CurrentElement);
                        MatthewsNamespace::MatthewStaticVariables::CopyMatrix->at(i).push_back(CurrentElement);
                        MatthewsNamespace::MatthewStaticVariables::MatrixForJ->at(i).push_back(CurrentElement);
                        MatthewsNamespace::MatthewStaticVariables::MatrixForR->at(i).push_back(CurrentElement);
                    }
                    catch (std::pair<int, std::string> ERRCODE)
                    {
                        std::cerr << ERRCODE.second << std::endl;
                    }
                }
            }
            // Check values -> Checked (Correct) 
            // printf("\nCopy Matrix\n");
            // ShowMatrix(std::cout, *MatthewsNamespace::MatthewStaticVariables::CopyMatrix);
            // printf("\nMatrix Julietta\n");
            // ShowMatrix(std::cout, *MatthewsNamespace::MatthewStaticVariables::MatrixForJ);
            // printf("\nMatrix Romeo\n");
            // ShowMatrix(std::cout, *MatthewsNamespace::MatthewStaticVariables::MatrixForR);
        }
        static void InitialiseMatrixWithZero(std::vector<std::vector<int>> &REFERENCED)
        {
            // Initialize for main matrix
            REFERENCED.clear();
            for (size_t i{}; i < MatthewStaticVariables::lines; ++i)
            {
                const size_t LITERAL = MatthewStaticVariables::lines;
                REFERENCED.push_back(std::vector<int>{});
                for (size_t j{}; j < MatthewStaticVariables::columns; ++j)
                {
                    REFERENCED.at(i).push_back(0);
                }
            }
            // Build the matrix graph after initialization
            // Set up the displacements
            DISPLACEMENT_COLS = static_cast<double>(*MatthewsNamespace::MatrixWindow::getLength()) / static_cast<double>(MatthewsNamespace::MatthewStaticVariables::columns);
            DISPLACEMENT_LINES = static_cast<double>(*MatthewsNamespace::MatrixWindow::getWidth()) / static_cast<double>(MatthewsNamespace::MatthewStaticVariables::columns);
            BuildTheMatrixGRAPH();
        }
        static void FillTheMatrixWithZeros(std::vector<std::vector<int>> &REFERENCED)
        {
            for (std::vector<std::vector<int>>::iterator it = REFERENCED.begin();
                 it != REFERENCED.end(); ++it)
            {
                for (std::vector<int>::iterator itersecond = it->begin(); itersecond != it->end(); ++itersecond)
                {
                    *itersecond = 0; // Using iterators for fast assignment
                }
            }
        }
        inline static bool IsInMatrix(size_t x, size_t y)
        {
            return x < MatthewStaticVariables::lines && x >= 0 && y < MatthewStaticVariables::columns && y >= 0 ? true : false;
        }
        static void BorderMatrix(std::vector<std::vector<int>> &REFERENCED)
        {
            // Not Needed -> Matrix starts from zero
        }

        static void BUILD_COLORED_SQUARES(std::vector<std::vector<int>>* OBJ){
            MatthewStaticVariables::getVectorOfTexts()->push_back(std::vector<sf::Text>{});
            for(size_t i {}; i< OBJ->size(); ++i){
                for(size_t j{} ; j<  OBJ->at(i).size(); ++j){
                    if(OBJ->at(j).at(i) !=0 && OBJ->at(j).at(i) !=-1 ){
                        // We found a path in the matrix
                        // So we color a rectangle
                        sf::RectangleShape Rect;
                        Rect.setFillColor(sf::Color::Red);
                        Rect.setPosition(sf::Vector2f(DISPLACEMENT_COLS/2 -DISPLACEMENT_COLS/2 + (i-1<0?0:i)*DISPLACEMENT_COLS, DISPLACEMENT_LINES/2 -DISPLACEMENT_COLS/2 + (j-1 < 0 ? 0:j)*DISPLACEMENT_LINES));
                        Rect.setSize(sf::Vector2f(DISPLACEMENT_COLS, DISPLACEMENT_LINES));
                        MatthewStaticVariables::getColoredInMatrix()->push_back(Rect);

                        // And we put the current step in it
                        sf::Text Txt; sf::Font Fnt;
                        Fnt.loadFromFile("FONTS/RMONO.ttf");
                        Txt.setFont(Fnt); Txt.setScale(sf::Vector2f(2, 1));
                        Txt.setString(std::to_string(OBJ->at(j).at(i))); Txt.setColor(sf::Color::Black);
                        Txt.setPosition(sf::Vector2f(DISPLACEMENT_COLS/2 -DISPLACEMENT_COLS/2 + (i-1<0?0:i)*DISPLACEMENT_COLS, DISPLACEMENT_LINES/2 -DISPLACEMENT_COLS/2 + (j-1 < 0 ? 0:j)*DISPLACEMENT_LINES));
                        MatthewStaticVariables::getVectorOfTexts()->at(MatthewStaticVariables::getVectorOfTexts()->size()-1).push_back(Txt);
                    }
                }
            }
            MatthewsObjectStatic::getVectorOfPossibleMatrices()->push_back(*MatthewStaticVariables::getColoredInMatrix());
            // printf("The final size of the texts array: %i", MatthewStaticVariables::getVectorOfTexts()->size());
            // printf("The final size of the blocks array: %i", MatthewsObjectStatic::getVectorOfPossibleMatrices()->size());
        }
        static void BuildTheMatrixGRAPH(){
            // We need lines-1 lines and cols-1 columns
            // They should be equally displaced from one another
            DISPLACEMENT_COLS = static_cast<double>(*MatthewsNamespace::MatrixWindow::getLength()) / static_cast<double>(MatthewsNamespace::MatthewStaticVariables::columns);
            DISPLACEMENT_LINES = static_cast<double>(*MatthewsNamespace::MatrixWindow::getWidth()) / static_cast<double>(MatthewsNamespace::MatthewStaticVariables::columns);
            printf("\nColumns displacement: %f\n",DISPLACEMENT_COLS);
            printf("\nLines displacement: %f\n\n",DISPLACEMENT_LINES);
            // Fill the column buffers
            for(size_t i{DISPLACEMENT_COLS} ; i<=*MatthewsNamespace::MatrixWindow::getLength() - DISPLACEMENT_COLS; i+=DISPLACEMENT_COLS){
                *MatthewStaticVariables::getVertexArrSize() = *MatthewStaticVariables::getVertexArrSize() +1;
                MatthewStaticVariables::getVertexofLines()[*MatthewStaticVariables::getVertexArrSize()] = sf::Vertex(sf::Vector2f(0, i), sf::Color::Blue);
                LINES->push_back(sf::Vector2f(0, i));

                *MatthewStaticVariables::getVertexArrSize() = *MatthewStaticVariables::getVertexArrSize() +1;
                MatthewStaticVariables::getVertexofLines()[*MatthewStaticVariables::getVertexArrSize()] = sf::Vertex(sf::Vector2f(*MatthewsNamespace::MatrixWindow::getWidth(), i), sf::Color::Blue);
                LINES->push_back(sf::Vector2f(*MatthewsNamespace::MatrixWindow::getWidth(), i));
            }
            // Fill the line buffers
            for(size_t i{DISPLACEMENT_LINES} ; i<=*MatthewsNamespace::MatrixWindow::getWidth() - DISPLACEMENT_LINES; i+=DISPLACEMENT_LINES){
                *MatthewStaticVariables::getVertexArrSize() = *MatthewStaticVariables::getVertexArrSize() +1;
                LINES->push_back(sf::Vector2f(i, 0));
                MatthewStaticVariables::getVertexofLines()[*MatthewStaticVariables::getVertexArrSize()] = sf::Vertex(sf::Vector2f(i, 0), sf::Color::Blue);
                
                *MatthewStaticVariables::getVertexArrSize() = *MatthewStaticVariables::getVertexArrSize() +1;
                LINES->push_back(sf::Vector2f(i, *MatthewsNamespace::MatrixWindow::getLength()));
                MatthewStaticVariables::getVertexofLines()[*MatthewStaticVariables::getVertexArrSize()] = sf::Vertex(sf::Vector2f(i, *MatthewsNamespace::MatrixWindow::getLength()), sf::Color::Blue);
            }
            // Fill the walls vector
            // We iterate through the matrix and scan for walls
            // And we push them in the vector of walls
            for(size_t i {}; i< MatthewsObjectStatic::getTheInitialisedMatrix()->size(); ++i){
                for(size_t j{} ; j<  MatthewsObjectStatic::getTheInitialisedMatrix()->at(i).size(); ++j){
                    if(MatthewsObjectStatic::getTheInitialisedMatrix()->at(j).at(i) == -1){
                        // We have a wall here, so we gotta draw a rectangle
                        sf::RectangleShape Rect;
                        Rect.setFillColor(sf::Color::Blue);
                        Rect.setPosition(sf::Vector2f(DISPLACEMENT_COLS/2 -DISPLACEMENT_COLS/2 + (i-1<0?0:i)*DISPLACEMENT_COLS, DISPLACEMENT_LINES/2 -DISPLACEMENT_COLS/2 + (j-1 < 0 ? 0:j)*DISPLACEMENT_LINES));
                        Rect.setSize(sf::Vector2f(DISPLACEMENT_COLS, DISPLACEMENT_LINES));
                        MatthewStaticVariables::getWallsInMatrix()->push_back(Rect);
                    }
                }
            }
        }

    public: // Getters
        static std::vector<sf::Vector2f>* getLINESGL () noexcept
        {
            return LINES;
        }
        static std::vector<sf::Vector2f>* getCOLUMNSGL () noexcept
        {
            return COLUMNS;
        }

        static std::array<std::array<int, 100>, 100> *getMatArray() noexcept
        {
            return MatrixArray;
        }
        static std::vector<std::vector<int>> *getOptimisedMatrix() noexcept
        {
            return MatrixInitial;
        }
        static int *getPositionInMatrix(std::vector<std::vector<int>> &REFERENCED, size_t xpos, size_t ypos) noexcept
        {
            return &REFERENCED.at(xpos).at(ypos);
        }
        static size_t &getLines() noexcept
        {
            return MatthewStaticVariables::lines;
        }
        static size_t &getColumns() noexcept
        {
            return MatthewStaticVariables::columns;
        }

    public: // Setters
        static void SetSize(size_t lin, size_t col)
        {
            MatthewStaticVariables::lines = lin;
            MatthewStaticVariables::columns = col;
        }
        static void SetLines(size_t value)
        {
            MatthewStaticVariables::lines = value;
        }
        static void SetColumns(size_t value)
        {
            MatthewStaticVariables::columns = value;
        }

    public:
        // Constructor - Destructor
        MatthewsObjectStatic();
        virtual ~MatthewsObjectStatic();

    public: // Algorithms
        static void LeesAlgorithmRecurisveOnMatrix(std::vector<std::vector<int>> &REFERENCED, size_t startpointx, size_t startpointy, size_t endpointx, size_t endpointy, size_t CURRENTVALUE_TOFILL)
        {
            if (MatthewsObjectStatic::IsInMatrix(startpointx, startpointy))
            {

                *MatthewsObjectStatic::getPositionInMatrix(REFERENCED, startpointx, startpointy) = CURRENTVALUE_TOFILL;
                // Conditions to recurse
                if (MatthewsObjectStatic::IsInMatrix(startpointx + 1, startpointy))
                {
                    if (*MatthewsObjectStatic::getPositionInMatrix(REFERENCED, startpointx + 1, startpointy) == 0 || (CURRENTVALUE_TOFILL + 1 < *MatthewsObjectStatic::getPositionInMatrix(*MatthewsObjectStatic::getOptimisedMatrix(), startpointx + 1, startpointy) && *MatthewsObjectStatic::getPositionInMatrix(*MatthewsObjectStatic::getOptimisedMatrix(), startpointx + 1, startpointy) != -1))
                    {
                        MatthewsObjectStatic::LeesAlgorithmRecurisveOnMatrix(REFERENCED, startpointx + 1, startpointy, endpointx, endpointy, CURRENTVALUE_TOFILL + 1);
                    }
                }
                if (MatthewsObjectStatic::IsInMatrix(startpointx - 1, startpointy))
                {
                    if (*MatthewsObjectStatic::getPositionInMatrix(REFERENCED, startpointx - 1, startpointy) == 0 || (CURRENTVALUE_TOFILL + 1 < *MatthewsObjectStatic::getPositionInMatrix(*MatthewsObjectStatic::getOptimisedMatrix(), startpointx - 1, startpointy) && *MatthewsObjectStatic::getPositionInMatrix(*MatthewsObjectStatic::getOptimisedMatrix(), startpointx - 1, startpointy) != -1))
                    {
                        MatthewsObjectStatic::LeesAlgorithmRecurisveOnMatrix(REFERENCED, startpointx - 1, startpointy, endpointx, endpointy, CURRENTVALUE_TOFILL + 1);
                    }
                }
                if (MatthewsObjectStatic::IsInMatrix(startpointx, startpointy + 1))
                    if (*MatthewsObjectStatic::getPositionInMatrix(REFERENCED, startpointx, startpointy + 1) == 0 || (CURRENTVALUE_TOFILL + 1 < *MatthewsObjectStatic::getPositionInMatrix(*MatthewsObjectStatic::getOptimisedMatrix(), startpointx, startpointy + 1) && *MatthewsObjectStatic::getPositionInMatrix(*MatthewsObjectStatic::getOptimisedMatrix(), startpointx, startpointy + 1) != -1))
                    {
                        MatthewsObjectStatic::LeesAlgorithmRecurisveOnMatrix(REFERENCED, startpointx, startpointy + 1, endpointx, endpointy, CURRENTVALUE_TOFILL + 1);
                    }
                if (MatthewsObjectStatic::IsInMatrix(startpointx, startpointy - 1))
                {
                    if (*MatthewsObjectStatic::getPositionInMatrix(REFERENCED, startpointx, startpointy - 1) == 0 || (CURRENTVALUE_TOFILL + 1 < *MatthewsObjectStatic::getPositionInMatrix(*MatthewsObjectStatic::getOptimisedMatrix(), startpointx, startpointy - 1) && *MatthewsObjectStatic::getPositionInMatrix(*MatthewsObjectStatic::getOptimisedMatrix(), startpointx, startpointy - 1) != -1))
                    {
                        MatthewsObjectStatic::LeesAlgorithmRecurisveOnMatrix(REFERENCED, startpointx, startpointy - 1, endpointx, endpointy, CURRENTVALUE_TOFILL + 1);
                    }
                }
            }
        }
        static void LeesAlgorithmWithHeapOnMatrix(std::vector<std::vector<int>> &REFERENCED, size_t startpointx, size_t startpointy, size_t endpointx, size_t endpointy)
        {
            // We gotta initialize a heap
            std::deque<MatthewStaticVariables::DATA_STRUCTURE> *GlobalQueue = new std::deque<MatthewStaticVariables::DATA_STRUCTURE>();
            // We push the first element on the heap
            MatthewStaticVariables::DATA_STRUCTURE *bar = new MatthewStaticVariables::DATA_STRUCTURE();
            // Setup bar
            printf("Lee's algorithm (heap version) has started\n");
            bar->xpos = startpointx;
            bar->ypos = startpointy;
            bar->value = 0;
            GlobalQueue->push_back(*bar);
            *MatthewsObjectStatic::getPositionInMatrix(REFERENCED, GlobalQueue->front().xpos, GlobalQueue->front().ypos) = GlobalQueue->front().value;
            delete bar;
            while (GlobalQueue->size() != 0)
            {
                // We have to check GlobalQueue -> Front
                if (MatthewsObjectStatic::IsInMatrix(GlobalQueue->front().xpos, GlobalQueue->front().ypos))
                {
                    // We check on all 4 directions
                    // DOWN
                    if (MatthewsObjectStatic::IsInMatrix(GlobalQueue->front().xpos + 1, GlobalQueue->front().ypos))
                    {
                        if (*MatthewsObjectStatic::getPositionInMatrix(REFERENCED, GlobalQueue->front().xpos + 1, GlobalQueue->front().ypos) == 0 ||
                            (GlobalQueue->front().value + 1 < *MatthewsObjectStatic::getPositionInMatrix(REFERENCED, GlobalQueue->front().xpos + 1, GlobalQueue->front().ypos) && *MatthewsObjectStatic::getPositionInMatrix(REFERENCED, GlobalQueue->front().xpos + 1, GlobalQueue->front().ypos) != -1))
                        {
                            // We add the object on the heap
                            MatthewStaticVariables::DATA_STRUCTURE *LOCDATA = new MatthewStaticVariables::DATA_STRUCTURE();
                            LOCDATA->xpos = GlobalQueue->front().xpos + 1;
                            LOCDATA->ypos = GlobalQueue->front().ypos;
                            LOCDATA->value = GlobalQueue->front().value + 1;
                            // We add it to the queue
                            GlobalQueue->push_back(*LOCDATA);
                            delete LOCDATA; // Frees up the memory
                        }
                    }
                    // UP
                    if (MatthewsObjectStatic::IsInMatrix(GlobalQueue->front().xpos - 1, GlobalQueue->front().ypos))
                    {
                        if (*MatthewsObjectStatic::getPositionInMatrix(REFERENCED, GlobalQueue->front().xpos - 1, GlobalQueue->front().ypos) == 0 ||
                            (GlobalQueue->front().value + 1 < *MatthewsObjectStatic::getPositionInMatrix(REFERENCED, GlobalQueue->front().xpos - 1, GlobalQueue->front().ypos) && *MatthewsObjectStatic::getPositionInMatrix(REFERENCED, GlobalQueue->front().xpos - 1, GlobalQueue->front().ypos) != -1))
                        {
                            // We add the object on the heap
                            MatthewStaticVariables::DATA_STRUCTURE *LOCDATA = new MatthewStaticVariables::DATA_STRUCTURE();
                            LOCDATA->xpos = GlobalQueue->front().xpos - 1;
                            LOCDATA->ypos = GlobalQueue->front().ypos;
                            LOCDATA->value = GlobalQueue->front().value + 1;
                            // We add it to the queue
                            GlobalQueue->push_back(*LOCDATA);
                            delete LOCDATA; // Frees up the memory
                        }
                    }
                    // RIGHT
                    if (MatthewsObjectStatic::IsInMatrix(GlobalQueue->front().xpos, GlobalQueue->front().ypos + 1))
                    {
                        if (*MatthewsObjectStatic::getPositionInMatrix(REFERENCED, GlobalQueue->front().xpos, GlobalQueue->front().ypos + 1) == 0 ||
                            (GlobalQueue->front().value + 1 < *MatthewsObjectStatic::getPositionInMatrix(REFERENCED, GlobalQueue->front().xpos, GlobalQueue->front().ypos + 1) && *MatthewsObjectStatic::getPositionInMatrix(REFERENCED, GlobalQueue->front().xpos, GlobalQueue->front().ypos + 1) != -1))
                        {
                            // We add the object on the heap
                            MatthewStaticVariables::DATA_STRUCTURE *LOCDATA = new MatthewStaticVariables::DATA_STRUCTURE();
                            LOCDATA->xpos = GlobalQueue->front().xpos;
                            LOCDATA->ypos = GlobalQueue->front().ypos + 1;
                            LOCDATA->value = GlobalQueue->front().value + 1;
                            // We add it to the queue
                            GlobalQueue->push_back(*LOCDATA);
                            delete LOCDATA; // Frees up the memory
                        }
                    }
                    // LEFT
                    if (MatthewsObjectStatic::IsInMatrix(GlobalQueue->front().xpos, GlobalQueue->front().ypos - 1))
                    {
                        if (*MatthewsObjectStatic::getPositionInMatrix(REFERENCED, GlobalQueue->front().xpos, GlobalQueue->front().ypos - 1) == 0 ||
                            (GlobalQueue->front().value + 1 < *MatthewsObjectStatic::getPositionInMatrix(REFERENCED, GlobalQueue->front().xpos, GlobalQueue->front().ypos - 1) && *MatthewsObjectStatic::getPositionInMatrix(REFERENCED, GlobalQueue->front().xpos, GlobalQueue->front().ypos - 1) != -1))
                        {
                            // We add the object on the heap
                            MatthewStaticVariables::DATA_STRUCTURE *LOCDATA = new MatthewStaticVariables::DATA_STRUCTURE();
                            LOCDATA->xpos = GlobalQueue->front().xpos;
                            LOCDATA->ypos = GlobalQueue->front().ypos - 1;
                            LOCDATA->value = GlobalQueue->front().value + 1;
                            // We add it to the queue
                            GlobalQueue->push_back(*LOCDATA);
                            delete LOCDATA; // Frees up the memory
                        }
                    }

                    *MatthewsObjectStatic::getPositionInMatrix(REFERENCED, GlobalQueue->front().xpos, GlobalQueue->front().ypos) = GlobalQueue->front().value;
                    // Modify the matrix and pop the last element
                    GlobalQueue->pop_front();
                }
            }
            *MatthewsObjectStatic::getPositionInMatrix(REFERENCED, startpointx, startpointy) = 0; // Reset the First value
            std::free(GlobalQueue); // Free up memory
        }
        static void BackTrackTheMatrix(std::vector<std::vector<int>> &REFERENCED, size_t startpointx, size_t startpointy, size_t endpointx, size_t endpointy, size_t CURRENTVALUE_TOFILL, MatrixWindow* MAT_WIND)
        {
            // We start moving recursively in the matrix
            // Starts like Lee
            if (MatthewsObjectStatic::IsInMatrix(startpointx, startpointy))
            {
                if(*MatthewsObjectStatic::getPositionInMatrix(REFERENCED, startpointx, startpointy)!=-1){
                    *MatthewsObjectStatic::getPositionInMatrix(REFERENCED, startpointx, startpointy) = CURRENTVALUE_TOFILL;
                }
                if(startpointx == endpointx && startpointy == endpointy){
                    *MatthewsObjectStatic::getOutFileForPathFind()<<"\n";
                    getColoredInMatrix()->clear(); // We clear the past colored positions
                    BUILD_COLORED_SQUARES(MatthewsObjectStatic::getTheInitialisedMatrix()); // We build the new positions based on the matrix
                    MatthewsNamespace::MatthewsObjectStatic::ShowMatrix(*MatthewsObjectStatic::getOutFileForPathFind(), REFERENCED);
                    // Ways of getting to xfin, yfin
                }
                // We check for all 4 positions, until our matrix is full
                // Conditions to recurse
                if (MatthewsObjectStatic::IsInMatrix(startpointx + 1, startpointy))
                {
                    if (*MatthewsObjectStatic::getPositionInMatrix(REFERENCED, startpointx + 1, startpointy) == 0 || (CURRENTVALUE_TOFILL + 1 < *MatthewsObjectStatic::getPositionInMatrix(*MatthewsObjectStatic::getOptimisedMatrix(), startpointx + 1, startpointy) && *MatthewsObjectStatic::getPositionInMatrix(*MatthewsObjectStatic::getOptimisedMatrix(), startpointx + 1, startpointy) != -1))
                    {
                        MatthewsObjectStatic::BackTrackTheMatrix(REFERENCED, startpointx + 1, startpointy, endpointx, endpointy, CURRENTVALUE_TOFILL + 1, MAT_WIND);
                    }
                }
                if (MatthewsObjectStatic::IsInMatrix(startpointx - 1, startpointy))
                {
                    if (*MatthewsObjectStatic::getPositionInMatrix(REFERENCED, startpointx - 1, startpointy) == 0 || (CURRENTVALUE_TOFILL + 1 < *MatthewsObjectStatic::getPositionInMatrix(*MatthewsObjectStatic::getOptimisedMatrix(), startpointx - 1, startpointy) && *MatthewsObjectStatic::getPositionInMatrix(*MatthewsObjectStatic::getOptimisedMatrix(), startpointx - 1, startpointy) != -1))
                    {
                        MatthewsObjectStatic::BackTrackTheMatrix(REFERENCED, startpointx - 1, startpointy, endpointx, endpointy, CURRENTVALUE_TOFILL + 1, MAT_WIND);
                    }
                }
                if (MatthewsObjectStatic::IsInMatrix(startpointx, startpointy + 1))
                    if (*MatthewsObjectStatic::getPositionInMatrix(REFERENCED, startpointx, startpointy + 1) == 0 || (CURRENTVALUE_TOFILL + 1 < *MatthewsObjectStatic::getPositionInMatrix(*MatthewsObjectStatic::getOptimisedMatrix(), startpointx, startpointy + 1) && *MatthewsObjectStatic::getPositionInMatrix(*MatthewsObjectStatic::getOptimisedMatrix(), startpointx, startpointy + 1) != -1))
                    {
                        MatthewsObjectStatic::BackTrackTheMatrix(REFERENCED, startpointx, startpointy + 1, endpointx, endpointy, CURRENTVALUE_TOFILL + 1, MAT_WIND);
                    }
                if (MatthewsObjectStatic::IsInMatrix(startpointx, startpointy - 1))
                {
                    if (*MatthewsObjectStatic::getPositionInMatrix(REFERENCED, startpointx, startpointy - 1) == 0 || (CURRENTVALUE_TOFILL + 1 < *MatthewsObjectStatic::getPositionInMatrix(*MatthewsObjectStatic::getOptimisedMatrix(), startpointx, startpointy - 1) && *MatthewsObjectStatic::getPositionInMatrix(*MatthewsObjectStatic::getOptimisedMatrix(), startpointx, startpointy - 1) != -1))
                    {
                        MatthewsObjectStatic::BackTrackTheMatrix(REFERENCED, startpointx, startpointy - 1, endpointx, endpointy, CURRENTVALUE_TOFILL + 1, MAT_WIND);
                    }
                }
                // If the recursion has ended here, we continue with the algo by resetting the current value to 0
                *MatthewsObjectStatic::getPositionInMatrix(REFERENCED, startpointx, startpointy) = 0;
            }
        }
        // RJ - FUNCS
        static void SearchROMEO(size_t ix, size_t iy, size_t jx, size_t jy){
            // We take Romeo's matrix
            // Random moves until he finds Julieta (backtracking) or Lee's algorithm (most efficient)
            MatthewsNamespace::MatthewsObjectStatic::LeesAlgorithmWithHeapOnMatrix(*MatthewStaticVariables::getRomeoMatrix(),ix, iy, jx, jy);

        }
        static void SearchJULIETA(size_t ix, size_t iy, size_t jx, size_t jy){
            // We take Julietta's matrix
            // Random moves until she finds Romeo (backtracking) or Lee's algorithm (most efficient)
            MatthewsNamespace::MatthewsObjectStatic::LeesAlgorithmWithHeapOnMatrix(*MatthewStaticVariables::getJulietaMatrix(),jx, jy, ix, iy);

        }
        static void DrawPathForRomeo(size_t ix, size_t iy, size_t iFIN, size_t jFIN){

        }
        static void FindOccurences(size_t iR, size_t jR, size_t iJ, size_t jJ){
            // To be run after the last two functions!
            for(size_t i{}; i<MatthewsObjectStatic::lines; ++i){
                for(size_t j{}; j<MatthewStaticVariables::columns;++j){
                    if(MatthewStaticVariables::getRomeoMatrix()->at(i).at(j) == MatthewStaticVariables::getJulietaMatrix()->at(i).at(j) && MatthewStaticVariables::getJulietaMatrix()->at(i).at(j) != -1 &&MatthewStaticVariables::getJulietaMatrix()->at(i).at(j)!=0){
                        // We found an efficient solution, so we start to fill the buffers
                        // We start with Julietta's position
                        printf("Found position %i ,%i\n",i, j);

                    }
                }
            }
        }
    };
} // namespace MatthewsNamespace

using namespace MatthewsNamespace;

int main(int argc, char** argv)
{
    if(argc == 1){
        std::cerr<<"\n~Too few Arguments to launch the program!~\n";
    }else if(argc == 6){
        printf("The argument count is 6, mode %s\n", argv[1]);
        printf("The arguments are: %i, %i, %i, %i\n", atoi(argv[2]), atoi(argv[3]), atoi(argv[4]), atoi(argv[5]));
        printf("The outputs of checkers are: %i, %i, %i, %i\n",isdigit(atoi(argv[2])), isdigit(atoi(argv[3])), isdigit(atoi(argv[4])), isdigit(atoi(argv[5])) );
        if(std::string(argv[1])=="Pathfind" && isdigit(atoi(argv[2]))+1 && isdigit(atoi(argv[3]))+1 && isdigit(atoi(argv[4]))+1 && isdigit(atoi(argv[5]))+1){
            printf("Executing the program as a path finder...\n");
            // Function needed for window threads
            XInitThreads(); 
            *MatthewStaticVariables::getPATH() = true;
            // Set the IPOSPATH and JPOSPATH
            *MatrixWindow::getiposPATH() = atoi(argv[3]);
            *MatrixWindow::getjposPATH() = atoi(argv[2]);
            // Initialize a graphical matrix
            MatthewsNamespace::MatrixWindow* MYMAIN = new MatthewsNamespace::MatrixWindow();
            // MatthewsNamespace::MatthewsObjectStatic::FillMatrixFromInput(std::cin);

            // Set a default size for our matrix

            //MatthewsObjectStatic::SetSize(4, 4);
            //MatthewsNamespace::MatthewsObjectStatic::InitialiseMatrixWithZero(*MatthewsNamespace::MatthewsObjectStatic::getOptimisedMatrix());
            MatthewsNamespace::MatthewsObjectStatic::IninialiseMatrixFromInput(*MatthewsNamespace::MatthewStaticVariables::getInFileWithMatrix(), *MatthewsNamespace::MatthewsObjectStatic::getOptimisedMatrix());
            // Filling the buffers for lines
            MatthewsNamespace::MatthewsObjectStatic::BuildTheMatrixGRAPH();
            MatthewsNamespace::MatthewsObjectStatic::ShowMatrix(std::cout, *MatthewsNamespace::MatthewsObjectStatic::getOptimisedMatrix());
            // MatthewsNamespace::MatthewsObjectStatic::LeesAlgorithmWithHeapOnMatrix(*MatthewsNamespace::MatthewsObjectStatic::getOptimisedMatrix(), 0, 0, 1, 1);
            MatthewsNamespace::MatthewsObjectStatic::getOptimisedMatrix()->at(atoi(argv[2])).at(atoi(argv[3])) = -1;
            
            MatthewsNamespace::MatthewsObjectStatic::BackTrackTheMatrix(*MatthewsNamespace::MatthewsObjectStatic::getOptimisedMatrix(), atoi(argv[2]), atoi(argv[3]), atoi(argv[4]), atoi(argv[5]), 0, MYMAIN);
            *MatthewsNamespace::MatthewStaticVariables::getOKSTART() = true;
            MatthewsObjectStatic::ResetAllMatrices();
            printf("\nWaiting for keyboard signal... ");
            std::cin.get();
        }else if(std::string(argv[1])=="RJ" && isdigit(atoi(argv[2]))+1 && isdigit(atoi(argv[3]))+1 && isdigit(atoi(argv[4]))+1 && isdigit(atoi(argv[5]))+1){
            // RJ Algorithm
            XInitThreads(); *MatthewStaticVariables::getRJ_H() = true;
            
            MatthewsNamespace::MatthewsObjectStatic::IninialiseMatrixFromInput(*MatthewsNamespace::MatthewStaticVariables::getInFileWithMatrix(), *MatthewsNamespace::MatthewsObjectStatic::getOptimisedMatrix());
            
            // MatthewsNamespace::MatrixWindow* MYMAIN = new MatthewsNamespace::MatrixWindow();
            // MatthewsNamespace::MatthewsObjectStatic::BuildTheMatrixGRAPH();

            printf("Starting the RJ algorithm using Lee's algo on heap\n");
            MatthewsNamespace::MatthewsObjectStatic::SearchROMEO(atoi(argv[2]), atoi(argv[3]), atoi(argv[4]), atoi(argv[5]));
            printf("~Romeo matrix after Lee~\n");
            MatthewsNamespace::MatthewStaticVariables::PRINT_MATRIX(std::cout, *MatthewsNamespace::MatthewStaticVariables::getRomeoMatrix());
            // Lee on Julieta
            MatthewsNamespace::MatthewsObjectStatic::SearchJULIETA(atoi(argv[2]), atoi(argv[3]), atoi(argv[4]), atoi(argv[5]));
            printf("\n~Julieta matrix after Lee~\n");
            MatthewsNamespace::MatthewStaticVariables::PRINT_MATRIX(std::cout, *MatthewsNamespace::MatthewStaticVariables::getJulietaMatrix());
            MatthewsObjectStatic::FindOccurences(atoi(argv[2]), atoi(argv[3]), atoi(argv[4]), atoi(argv[5]));
            MatthewsObjectStatic::ResetAllMatrices();
            printf("\nWaiting for keyboard signal... ");
            std::cin.get();
        }else if(std::string(argv[1])=="RJ-S" && isdigit(atoi(argv[2]))+1 && isdigit(atoi(argv[3]))+1 && isdigit(atoi(argv[4]))+1 && isdigit(atoi(argv[5]))+1){
            printf("Starting the RJ algorithm using Lee's algo on stack\n");
            MatthewsNamespace::MatthewStaticVariables::PRINT_MATRIX(std::cout, *MatthewsNamespace::MatthewStaticVariables::getRomeoMatrix());
        }
    }
}
