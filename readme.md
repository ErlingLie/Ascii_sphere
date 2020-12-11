# Sphere ASCII animation

Project to procrastinate from Examen Philosoficum....

Largely inspired by [this](https://www.a1k0n.net/2011/07/20/donut-math.html)

## Geometry
The sphere is generated with spherical coordinates.

<img src="https://render.githubusercontent.com/render/math?math=x = \rho cos(\phi) cos(\theta)">
<img src="https://render.githubusercontent.com/render/math?math=y = \rho sin(\theta)">
<img src="https://render.githubusercontent.com/render/math?math=z = \rho cos(\phi) sin(\theta)">
As we can only see half of the sphere anyways, theta runs from [-\pi, 0] and \phi runs from [-\pi/2, \pi/2] creating a half sphere.


## Illumination model

The code uses a [Phong illumination model] (https://en.wikipedia.org/wiki/Phong_reflection_model). 

<img src="https://render.githubusercontent.com/render/math?math=I = I_i(k_d (\mathbf{\hat{n}\cdot \hat{l}}) + k_s (\mathbf{\hat{n} \cdot \hat{h}})^n )">
