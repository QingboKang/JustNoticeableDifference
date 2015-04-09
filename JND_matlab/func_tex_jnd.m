function matout = func_tex_jnd(matin)

% estimate the texture masking distortion

if ~isa(matin, 'double')
    matin = double(matin);
end

G1 = [0 0 0 0 0
   1 3 8 3 1
   0 0 0 0 0
   -1 -3 -8 -3 -1
   0 0 0 0 0];

G2=[0 0 1 0 0
   0 8 3 0 0
   1 3 0 -3 -1
   0 0 -3 -8 0
   0 0 -1 0 0];

G3=[0 0 1 0 0
   0 0 3 8  0
   -1 -3 0 3 1
   0 -8 -3 0 0
   0 0 -1 0 0];

G4=[0 1 0 -1 0
   0 3 0 -3 0
   0 8 0 -8 0
   0 3 0 -3 0
   0 1 0 -1 0];

% calculate the max grad
[size_x,size_y]=size(matin);
grad=zeros(size_x,size_y,4);
grad(:,:,1) = filter2(G1,matin)/16;
grad(:,:,2) = filter2(G2,matin)/16;
grad(:,:,3) = filter2(G3,matin)/16;
grad(:,:,4) = filter2(G4,matin)/16;
maxgard = max( abs(grad), [], 3 );

bg_lum = func_bg_lum(matin);

LANDA = 1/2;
alpha = 0.0001*bg_lum+0.115;
belta = LANDA-0.01*bg_lum;
matout = maxgard.*alpha + belta;
img_tex = mat2gray(matout);
figure, imshow(img_tex), title('spatial mask');