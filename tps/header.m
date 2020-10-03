%%% HEADER
clear all;
close all;

% FID = fopen('lena.jpg');

lena = imread('lenna.bmp');
figure;
imshow(lena)
info = imfinfo('lena.bmp');

lenag = rgb2gray(lena);
imwrite(lenag,'lena_gris.png');
info_gris = imfinfo('lena_gris.png');




%% TRANSFORMADA COSENO
load imagenes.mat
lena = mat2gray(foto_lenna);
B = dct2(lena);
imwrite(B,'lena_dct','bmp');
mrec = idct2(B);
imwrite(mrec,'lena_rec','bmp');
%figure;
%imshow(log(abs(B)),[]), colormap(gca,jet), colorbar

k=10000;
fig=figure;
hold on;
imhist(lena,256);
imhist(B,256);

legend('Original','DCT');
print(fig,'hist_dct','-dpng','-r0');



%% BORDES RECORRIDO NORMAL (horizontal)
clear all;
close all;

load imagenes.mat
% [N,M] = size(foto_lenna);
lena = mat2gray(foto_lenna);
% lena = imread('rayas.jpg');
[N,M] = size(lena);
borde1 = ones(N,M);
umbral = 0.05; 
dif = zeros(N*M,1);
n = 1;
for i=1:N
    for j=1:M-1
        dif(n)= lena(i,j)-lena(i,j+1);
        n = n +1;
        if abs(lena(i,j)-lena(i,j+1))>umbral
        borde1(i,j) = 0;
        end
    end
end
fig=figure;
histogram(dif);
xlim([-0.26 0.26]);
print(fig,'dif_h','-dpng','-r0');
fig=figure;
imshow(borde1);
print(fig,'rayas_borde_h','-dpng','-r0');
%% BORDES RECORRIDO NORMAL (vertical)
clear dif;
% [N,M] = size(foto_lenna);
% lena = mat2gray(foto_lenna);
borde2 = ones(N,M);
umbral = 0.05; 
dif = zeros(N*M,1);
n=1;
for j=1:M
    for i=1:N-1
        dif(n) = lena(i,j)-lena(i+1,j);
        n = n+1;
        if abs(lena(i,j)-lena(i+1,j))>umbral
        borde2(i,j) = 0;
        end
    end
end
fig=figure;
histogram(dif);
xlim([-0.22 0.22]);
print(fig,'dif_v','-dpng','-r0');
fig=figure;
imshow(borde2);
print(fig,'rayas_borde_v','-dpng','-r0');
total = 1-((1-borde1) + (1-borde2));


fig=figure;
imshow((total));
print(fig,'rayas_borde_t','-dpng','-r0');
%% BORDES CON HILBERT
clear all;
close all;

load imagenes.mat;
lena = mat2gray(foto_lenna);
[N,M] = size(lena);

borde = ones(N,M);
umbral = 0.05; 
[x,y] = hilbert(9);
figure;
plot(x,y);

x_min = min(x);


x = (x - x_min)/0.001953125 +1;
y = (y - x_min)/0.001953125 +1;

delta = zeros(length(x),1);

for n=1:length(x)-1
    if abs(lena(x(n),y(n))-lena(x(n+1),y(n+1)))>umbral
        borde(x(n),y(n)) = 0;
    end
    delta(n) = lena(x(n),y(n))-lena(x(n+1),y(n+1));
end

fig=figure;
imshow(borde);
print(fig,'borde_hilb','-dpng','-r0');

fig=figure;
histogram(delta);
xlim([-0.22 0.22]);
print(fig,'delta_hilb','-dpng','-r0');

[x,y] = hilbert(3);
fig=figure;
plot(x,y);
print(fig,'recorrido_hilb','-dpng','-r0');
%% BORDES POR VENTANA -> recorrido horizontal

borde = ones(N,M);
umbral = 0.03;

for i=1:N-2
    for j=1:M-2
        if(mean(lena(i:i+1,j:j+1))-mean(lena(i+1:i+2,j+1:j+2)))>umbral
            borde(i,j) = 0;
        end
    end
end
figure;
imshow(borde);

%% BORDES POR VENTANA -> recorrido vertical 
clear borde;
borde = ones(N,M);
umbral = 0.03;

for j=1:M-2
    for i=1:N-2
        if(mean(lena(i:i+1,j:j+1))-mean(lena(i+1:i+2,j+1:j+2)))>umbral
            borde(i,j) = 0;
        end
    end
end
figure;
imshow(borde);

%% HISTOGRAMA Y ECUALIZACION
clear all;
close all;

load imagenes.mat;
lena = mat2gray(foto_lenna);

[N,M] = size(lena);

% figure;
% histogram(lena);
k=10000;
[r,edges]=histcounts(lena,k);
fig=figure;
plot(r);
print(fig,'hist_r','-dpng','-r0');
[s,~]=histcounts(lena,k,'Normalization','cdf');
fig=figure;
plot(s);
print(fig,'hist_s','-dpng','-r0');

for i=1:N
    for j=1:M
        [~,n]=min(abs(edges(1:end-1)-ones(1,length(edges(1:end-1)))*lena(i,j)));
        lena(i,j)=s(n);
    end
end

fig=figure;
histogram(lena,'Normalization','pdf');
print(fig,'hist_obt','-dpng','-r0');

fig=figure;
imshow(lena);
print(fig,'lena_ec','-dpng','-r0');
%% STREECHING 5 Y 95
clear all;
close all;

load imagenes.mat;
lena = mat2gray(foto_lenna);

[N,M] = size(lena);

k=100;
[r,edges]=histcounts(lena,k,'Normalization','count');

mu_min = -1;
mu_max = -1;
aux1=0;
aux2=0;
for i=1:length(r)
    if (aux1+r(i))/sum(r) >= 0.5 && mu_min == -1
        mu_min = edges(i);
    end
    if (aux2+r(end+1-i))/sum(r) >= 0.0005 && mu_max == -1
        mu_max = edges(end+1-i);
    end
    aux1=aux1+r(i);
    aux2=aux2+r(end+1-i);
end

for i=1:N
    for j=1:M
        lena(i,j)=lena(i,j)*255/(mu_max-mu_min);
    end
end

lena =mat2gray (lena);
fig=figure;
histogram(lena,'Normalization','pdf');
print(fig,'hist_str','-dpng','-r0');

fig=figure;
imshow(lena);
print(fig,'lena_str','-dpng','-r0');
%% ZOOM 
clear all;
close all;

load imagenes.mat;
lena = mat2gray(foto_lenna);
[out0, out1] = zoom0(lena);

fig=figure;
imshow(out0(1:512,1:512));
print(fig,'zoom0_1cuadrante','-dpng','-r0');

fig=figure;
imshow(out0(1:512,512:1024));
print(fig,'zoom0_2cuadrante','-dpng','-r0');

fig=figure;
imshow(out0(512:1024,1:512));
print(fig,'zoom0_3cuadrante','-dpng','-r0');

fig=figure;
imshow(out0(512:1024,512:1024));
print(fig,'zoom0_4cuadrante','-dpng','-r0');


fig=figure;
imshow(out1(1:512,1:512));
print(fig,'zoom1_1cuadrante','-dpng','-r0');

fig=figure;
imshow(out1(1:512,512:1024));
print(fig,'zoom1_2cuadrante','-dpng','-r0');

fig=figure;
imshow(out1(512:1024,1:512));
print(fig,'zoom1_3cuadrante','-dpng','-r0');

fig=figure;
imshow(out1(512:1024,512:1024));
print(fig,'zoom1_4cuadrante','-dpng','-r0');

[out0, ~] = zoom0(out0(1:512,1:512));
[~, out1] = zoom0(out1(1:512,1:512));

fig=figure;
imshow(out0(1:512,1:512));
print(fig,'zoom0_1cuadrante4','-dpng','-r0');

fig=figure;
imshow(out0(1:512,512:1024));
print(fig,'zoom0_2cuadrante4','-dpng','-r0');

fig=figure;
imshow(out0(512:1024,1:512));
print(fig,'zoom0_3cuadrante4','-dpng','-r0');

fig=figure;
imshow(out0(512:1024,512:1024));
print(fig,'zoom0_4cuadrante4','-dpng','-r0');


fig=figure;
imshow(out1(1:512,1:512));
print(fig,'zoom1_1cuadrante4','-dpng','-r0');

fig=figure;
imshow(out1(1:512,512:1024));
print(fig,'zoom1_2cuadrante4','-dpng','-r0');

fig=figure;
imshow(out1(512:1024,1:512));
print(fig,'zoom1_3cuadrante4','-dpng','-r0');

fig=figure;
imshow(out1(512:1024,512:1024));
print(fig,'zoom1_4cuadrante4','-dpng','-r0');

%% K-MEANS

clear all;
close all;
lenna_kmeans ={'Imagen_Lenna_3colores' ;'Imagen_Lenna_5colores';'Imagen_Lenna_10colores';'Imagen_Lenna_30colores';'Imagen_Lenna_60colores';};
load imagenes.mat;
lena = mat2gray(foto_lenna);

[N,M] = size(lena);

lena_vec = reshape(lena,N*M,1);

rng(1); % For reproducibility
n=[3 5 10 30 60];
for k=1:length(n)
[idx,C] = kmeans(lena_vec,n(k));

for i=1:M*N
    lena_aux(i) = C(idx(i));
end
lena_aux = reshape(lena_aux,M,N);
fig=figure;
imshow(lena_aux);
print(fig,lenna_kmeans{k},'-dpng','-r0');
end