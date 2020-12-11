#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <vector>
#include <cmath>
#include <cstdio>

constexpr double pi = 3.141592;

inline std::vector<double> normalized_vector(double x, double y, double z){
    std::vector<double> vec{x,y,z};
    double vec_length = sqrt(x*x + y*y + z*z);
    vec[0] /= vec_length;
    vec[1] /= vec_length;
    vec[2] /= vec_length;
    return vec;
}

inline double dot(std::vector<double>& a, std::vector<double>& b){
    double res = 0;
    for (int i{0}; i<a.size(); ++i){
        res += a[i]*b[i];
    }
    return res;
}

int main(){
    
    int screen_width = 60;
    int screen_height = 30;
    const double radius = 1.0;
    const double K2 = 10;
    const double K1 = screen_width*K2*3/(8*radius);
    const double K3 = screen_height*K2*3/(8*radius);
    const double light_radius = 30;
    const double light_denominator = sqrt(light_radius*light_radius + 1);
    const double lighty = 1.0/light_denominator;
    const double kd = .1;
    const double ks = 1.0-kd;

    double light_angle = 0.0;
    while (true){
        light_angle = light_angle < 2*pi ? light_angle + 0.03 : 0;

        std::vector<double> light{cos(light_angle)*light_radius / light_denominator,
                                lighty,
                                sin(light_angle)*light_radius / light_denominator};

        std::vector<std::vector<double>> zBuffer(screen_width,std::vector<double>(screen_height, -10.0));
        std::vector<std::vector<char>>  outBuffer(screen_width,std::vector<char>(screen_height, ' '));
        for(double theta{0.0};theta > -pi ; theta -= 0.03 ) {
            for (double phi{-pi/2}; phi < pi/2; phi += 0.03){
                // Coordinates of object
                double z = radius*cos(phi)*sin(theta);
                double y = radius*sin(phi);
                double x = radius*cos(phi)*cos(theta);               

                // Lighting
                std::vector<double> normal{x/radius, y/radius, z/radius};
                double diffuse = std::max(dot(normal, light), 0.0);

                std::vector<double> v = normalized_vector(-x, -y, -z - K2);

                std::vector<double> h = normalized_vector((light[0] + v[0])/2, 
                                                         (light[1] + v[1])/2,
                                                         (light[2] + v[2])/2);
                

                double specular = dot(normal, h);
                double spec = 1;
                for (int i{0}; i<5; ++i){
                    spec*= specular;
                }
                int L = static_cast<int>(12*(kd*diffuse + ks*spec));
                if (L >= 0){
                    // Screen coordinates
                    double ooz = 1/(z + K2);
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
        usleep(5000);
    }
    return 0;

}