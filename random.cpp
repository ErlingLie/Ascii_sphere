#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <vector>
#include <cmath>
#include <cstdio>

constexpr float pi = 3.141592;
int main(){
    
    int screen_width = 60;
    int screen_height = 30;
    const float radius = 1.0;
    const float K2 = 10;
    const float K1 = screen_width*K2*3/(8*radius);
    const float K3 = screen_height*K2*3/(8*radius);
    const float light_radius = 30;
    const float light_denominator = sqrt(light_radius*light_radius + 100);
    const float lighty = 10.0f/light_denominator;
    float light_angle = 0.0f;
    while (true){
        light_angle = light_angle < 2*pi ? light_angle + 0.03 : 0;

        float lightx = cos(light_angle)*light_radius / light_denominator;
        float lightz = -sin(light_angle)*light_radius / light_denominator;

        std::vector<std::vector<float>> zBuffer(screen_width,std::vector<float>(screen_height, -10.0f));
        std::vector<std::vector<char>>  outBuffer(screen_width,std::vector<char>(screen_height, ' '));
        for(float theta{0.0};theta < pi ; theta += 0.01 ) {
            for (float phi{-pi/2}; phi < pi/2; phi += 0.01){
                // Coordinates of object
                float z = -radius*cos(phi)*sin(theta) + K2;
                float y = radius*sin(phi);
                float x = radius*cos(phi)*cos(theta);               

                // Lighting
                float cosA = std::max(x/radius * lightx + y/radius*lighty + (z-K2)/radius*lightz, 0.0f);
                float cosB = -(z-K2)/radius;
                int L = static_cast<int>(6*(cosA + cosB));

                if (L >= 0){
                    // Screen coordinates
                    float ooz = 1/z;
                    int xp = static_cast<int>(screen_width/2 + K1*ooz*x);
                    int yp = static_cast<int>(screen_height/2 - K3*ooz*y);
                    if (ooz > zBuffer[xp][yp]){
                        zBuffer[xp][yp] = ooz;
                        outBuffer[xp][yp] = ".,-~:;=!*#$@"[L];
                    }
                }

            }        
        }
        printf("\033[2J");
        printf("\x1b[H");
        for (int j = 0; j < screen_height; j++) {
            for (int i = 0; i < screen_width; i++) {
            putchar(outBuffer[i][j]);
            }
            putchar('\n');
        }
        usleep(10000);
    }
    return 0;

}