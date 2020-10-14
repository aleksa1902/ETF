function zadatak1
%% Def parameters

A = mod((118+2017),7)+1;
B = mod((578+2017),4)+3;
f1 = 5*(mod((1+1+8),4)+1);
f2 = 3*(mod((5+7+8),4)+1);
%P = mod((578+118),3)+1;
%Q = mod((1+1+8+5+7+8),8)+1;

%% Def ulaza, h(x), s(x), y(x)

inputs = 0:0.001:1;

outputs = A*sin(2*pi*f1*inputs)+B*sin(2*pi*f2*inputs);

std =(0.2 * min(A,B)).*randn(1,length(inputs));

finaly = outputs + std;

%% Crtanje funkcije

plot(inputs, finaly, 'g', inputs, outputs, 'r' );
title('Predikciona funkcija i konacna funkcija');
legend('y(x)','h(x)');

%% Def broja clanova ulaza/izlaza, shuffile & split train and test

number = size(finaly, 2);

% Split train and test
number_train = 0.8*number;
number_test  = 0.2*number;

% Suffile
idx = randperm(number);

%% Podela podataka na train and test

% Train
inputs_train = inputs(:, idx(1 : number_train));
finaly_train = finaly(:, idx(1 : number_train));

% Test
inputs_test = inputs(:, idx(number_train+1 : number));
finaly_test = finaly(:, idx(number_train+1 : number));

%% Kreiranje neuralne mreze

NN = feedforwardnet(50);

NN.divideFcn = ""; 
%NN.trainParam.goal = 0.00001;

% Treniranje neuralne mreze
NN = train(NN,inputs_train,finaly_train);

a = sim(NN,inputs_test);

% Crtanje grafika neuralne mreze
figure;
plot(inputs, finaly, 'r', inputs, NN(inputs), 'b');
title('Predikcija neuralne mreze');
legend('y(x)','NN');