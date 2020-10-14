function zadatak2
%% Dohvatanje podataka
%mod(a,b)
%mod((118+578),3)+1; radim dataset1

values = load('dataset1.mat');
matrix = values.data;

%% Podaci

inputs = matrix(:,1:2)';
resultsZero = matrix(1:1000,1:2)'; 
resultsOne = matrix(1001:2000,1:2)'; 
finaly = matrix(:,3)';

%% Crtanje rezultata sa nulama i jedinicama

figure;
    plot(resultsZero(1,:),resultsZero(2,:),'go');
    hold on;
    plot(resultsOne(1,:),resultsOne(2,:),'ro');
    legend('resultsZero','resultsOne');
    
%% Def broja clanova ulaza/izlaza, shuffile & split train and test

number = length(inputs(1,:));

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

%% clasic neural network

NN = patternnet([3 4]);

    NN.divideFcn = '';
    NN.trainParam.epochs = 1000;
    NN.trainParam.goal = 1e-3;
    NN.trainParam.min_grad = 1e-9;
    NN.trainParam.min_grad = 1e-8;
    
    NN = train(NN,inputs_train,finaly_train);
    
    a = sim(NN, inputs_test);
    
%% Pravljenje confusion matric

    output_a = sim(NN,inputs_train);
    
figure;
    plotconfusion(finaly_train,output_a);
    title('Trening konfuziona matrica');
    
figure;
    plotconfusion(finaly_test, a);
    title('Test konfuziona matrica');

    correctZero = inputs_test(:,finaly_test==0); 
    correctOne = inputs_test(:,finaly_test==1);  

    numbersPoint = 100; 
    xLimit = linspace(-4, 4, numbersPoint); 
    yLimit = linspace(-2, 6, numbersPoint); 
    
    input_test_limit = [];

    for i = xLimit
        input_test_limit = [input_test_limit [i*ones(size(yLimit)); yLimit]];
    end

    outTest = sim(NN, input_test_limit); 
    limitResultsZero = input_test_limit(:,outTest<0.5); 
    limitResultsOne = input_test_limit(:,outTest>=0.5); 
    
    figure;
    hold all;
        plot(correctZero(1,:),correctZero(2,:),'bo');
        plot(correctOne(1,:),correctOne(2,:),'k*');
        scatter(limitResultsZero(1,:), limitResultsZero(2,:),'g.');
        scatter(limitResultsOne(1,:),limitResultsOne(2,:),'r.');
        title('Granice odlucivanja');
        legend('resultsZero','resultsOne','GranicaResultsZero','GranicaResultsOne');
        
%% Parametri preciznosti i osetljivosti

    [~,trainT,~,~] = confusion(finaly_train,output_a);
    trainTransp = trainT';
    [~,testT,~,~] = confusion(finaly_test,a);
    testTransp = testT';

    precisionTrain = trainTransp(1,1)/sum(trainTransp(1,:));
    precisionTest = testTransp(1,1)/sum(testTransp(1,:));
    
    recallTrain = trainTransp(1,1)/sum(trainTransp(:,1));      
    recallTest = testTransp(1,1)/sum(testTransp(:,1));    
    
%% Overfiting

NN = patternnet([6 6 6]);  

    NN.divideFcn = '';        
    NN.trainParam.epochs = 1000; 
    NN.trainParam.goal = 1e-3;
    NN.trainParam.min_grad = 1e-9;
    NN = train(NN,inputs_train,finaly_train);
    
    a = sim(NN, inputs_test);
    
%% Pravljenje confusion matric

    output_a = sim(NN,inputs_train);
    
figure;
    plotconfusion(finaly_train,output_a);
    title('Trening konfuziona matrica');
    
figure;
    plotconfusion(finaly_test, a);
    title('Test konfuziona matrica');

    correctZero = inputs_test(:,finaly_test==0); 
    correctOne = inputs_test(:,finaly_test==1);  

    numbersPoint = 100; 
    xLimit = linspace(-4, 4, numbersPoint); 
    yLimit = linspace(-2, 6, numbersPoint); 
    input_test_limit = [];

    for i = xLimit
        input_test_limit = [input_test_limit [i*ones(size(yLimit)); yLimit]];
    end

    outTest = sim(NN, input_test_limit); 
    limitResultsZero = input_test_limit(:,outTest<0.5); 
    limitResultsOne = input_test_limit(:,outTest>=0.5); 
    
    figure;
    hold all;
        plot(correctZero(1,:),correctZero(2,:),'bo');
        plot(correctOne(1,:),correctOne(2,:),'k*');
        scatter(limitResultsZero(1,:), limitResultsZero(2,:),'g.');
        scatter(limitResultsOne(1,:),limitResultsOne(2,:),'r.');
        title('Granice odlucivanja');
        legend('resultsZero','resultsOne','GranicaResultsZero','GranicaResultsOne');
        
%% Parametri preciznosti i osetljivosti

    [~,trainT,~,~] = confusion(finaly_train,output_a);
    trainTransp = trainT';
    [~,testT,~,~] = confusion(finaly_test,a);
    testTransp = testT';

    precisionTrain = trainTransp(1,1)/sum(trainTransp(1,:));
    precisionTest = testTransp(1,1)/sum(testTransp(1,:));
    
    recallTrain = trainTransp(1,1)/sum(trainTransp(:,1));      
    recallTest = testTransp(1,1)/sum(testTransp(:,1)); 
    
%% Underfiting

NN = patternnet(4); 

    NN.divideFcn = '';        
    NN.trainParam.epochs = 1000; 
    NN.trainParam.goal = 1e-3;
    NN.trainParam.min_grad = 1e-9;
    NN = train(NN,inputs_train,finaly_train);
    
    a = sim(NN, inputs_test);
    
%% Pravljenje confusion matric

    output_a = sim(NN,inputs_train);
    
figure;
    plotconfusion(finaly_train,output_a);
    title('Trening konfuziona matrica');
    
figure;
    plotconfusion(finaly_test, a);
    title('Test konfuziona matrica');

    correctZero = inputs_test(:,finaly_test==0); 
    correctOne = inputs_test(:,finaly_test==1);  

    numbersPoint = 100; 
    xLimit = linspace(-4, 4, numbersPoint); 
    yLimit = linspace(-2, 6, numbersPoint); 
    input_test_limit = [];

    for i = xLimit
        input_test_limit = [input_test_limit [i*ones(size(yLimit)); yLimit]];
    end

    outTest = sim(NN, input_test_limit); 
    limitResultsZero = input_test_limit(:,outTest<0.5); 
    limitResultsOne = input_test_limit(:,outTest>=0.5); 
    
    figure;
    hold all;
        plot(correctZero(1,:),correctZero(2,:),'bo');
        plot(correctOne(1,:),correctOne(2,:),'k*');
        scatter(limitResultsZero(1,:), limitResultsZero(2,:),'g.');
        scatter(limitResultsOne(1,:),limitResultsOne(2,:),'r.');
        title('Granice odlucivanja');
        legend('resultsZero','resultsOne','GranicaResultsZero','GranicaResultsOne');
        
%% Parametri preciznosti i osetljivosti

    [~,trainT,~,~] = confusion(finaly_train,output_a);
    trainTransp = trainT';
    [~,testT,~,~] = confusion(finaly_test,a);
    testTransp = testT';

    precisionTrain = trainTransp(1,1)/sum(trainTransp(1,:));
    precisionTest = testTransp(1,1)/sum(testTransp(1,:));
    
    recallTrain = trainTransp(1,1)/sum(trainTransp(:,1));      
    recallTest = testTransp(1,1)/sum(testTransp(:,1)); 