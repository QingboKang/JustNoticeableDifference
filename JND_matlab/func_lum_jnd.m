function matout = func_lum_jnd(matin)

% estimate the background luminance distortion

if ~isa(matin, 'double')
    matin = double(matin);
end

bg_lum = func_bg_lum(matin);

[col, row] = size(matin);

matout = zeros(col, row);
bg_jnd = lum_jnd;
for x = 1:col
    for y = 1:row
        matout(x,y) = bg_jnd( bg_lum(x,y)+1 );
    end
end
img_bg_jnd = mat2gray(matout);
figure, imshow(img_bg_jnd), title('luminance adaptation jnd');

%--------------------------------------
function bg_jnd = lum_jnd
bg_jnd = zeros(256, 1); 
T0 = 17;
gamma = 3 / 128;
for k = 1 : 256
    lum = k-1;
    if lum <= 127
        bg_jnd(k) =  T0 * (1 - sqrt( lum/127)) + 3;
    else
        bg_jnd(k) = gamma * (lum-127) + 3;
    end
end