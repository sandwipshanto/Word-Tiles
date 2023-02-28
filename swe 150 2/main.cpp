#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <string>
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1300, 800), "Word Tiles");
    sf::Texture t;
    t.loadFromFile("ad.jpg");
    sf::Sprite s(t);
    sf::Font font;
    font.loadFromFile("arial.ttf");
    std::vector<sf::Text> blocks;
    std::string letters = "abcdefghijklmnopqrstuvwxyz";
    int score = 0;
    int wrong=5;
    int lno = rand()%26;
    double m=0.25;
    //score count
    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setPosition(10, 10);
    scoreText.setFillColor(sf::Color::White);


     //gameover
    sf::Text GameOverText;
    GameOverText.setFont(font);
    GameOverText.setCharacterSize(100);
    GameOverText.setPosition(360, 180);
    GameOverText.setFillColor(sf::Color::Yellow);

     //wrongcount
    sf::Text wrongText;
    wrongText.setFont(font);
    wrongText.setCharacterSize(24);
    wrongText.setPosition(10, 50);
    wrongText.setFillColor(sf::Color::White);

    //showscrore
    sf::Text SscoreText;
    SscoreText.setFont(font);
    SscoreText.setCharacterSize(24);
    SscoreText.setPosition(560, 600);
    SscoreText.setFillColor(sf::Color::White);


    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)

                window.close();
                scoreText.setString("Score: " + std::to_string(score));
                 wrongText.setString("Life: " + std::to_string(wrong));

            if (event.type == sf::Event::TextEntered)
            {
                char c = static_cast<char>(event.text.unicode);
                if (c == letters[lno % 26])
                {
                    blocks.clear();
                    score++;
                    if(score%3==0)
                        m=m+0.25;
                    lno=rand()%26;
                    scoreText.setString("Score: " + std::to_string(score));


                }

                else {
                    if(wrong>0) wrong--;
                    else wrong=5;
                    wrongText.setString("Life: " + std::to_string(wrong));
                }

            }
        }
        if (blocks.empty() || blocks.back().getPosition().y > 800)
        {
            sf::Text block;
            block.setFont(font);
            block.setCharacterSize(60);
            block.setFillColor(sf::Color::White);
//            block.setString(letters.substr(score % 26, 1));
            block.setString(letters.substr(lno, 1));
            block.setPosition( rand() % 1000 + 200, 0);

            blocks.push_back(block);

        }



        for (auto& block : blocks)
        {
            block.move(0, m);
        if(block.getPosition().y + 60 >= window.getSize().y)
        {
            wrong--;
            wrongText.setString("Life: " + std::to_string(wrong));
            blocks.clear();
            //break;

        }
            if (wrong==0)

                blocks.clear();

        }
        window.clear();
         window.draw(s);
         if(wrong==0) {
                GameOverText.setString("GAME OVER ");
                SscoreText.setString("Your Score: " + std::to_string(score));

         }

        for (const auto& block : blocks)
            window.draw(block);


       if(wrong>0){
                window.draw(scoreText);
        window.draw(wrongText);
       }

        else  {

                window.draw(GameOverText);

                window.draw(SscoreText);
        }

        window.display();
    }
    //std::cout<<"Your score is: "<<score<<std::endl;

    return 0;
}

