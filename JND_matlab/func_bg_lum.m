function matout = func_bg_lum(matin)

% calculate the average background luminance of the image
if ~isa(matin, 'double')
    matin = double(matin);
end

B=[1 1 1 1 1
   1 2 2 2 1
   1 2 0 2 1
   1 2 2 2 1
   1 1 1 1 1];
matout = floor( filter2(B, matin) / 32 );