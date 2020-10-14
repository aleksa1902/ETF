clc, clear, close all

load pendigits.tra
pendigits=transpose(pendigits);
Xtrain = pendigits(1:16,:);
Ntrain = length(Xtrain);

Ytrain=zeros(10,Ntrain);
for i=1:length(pendigits)
    Ytrain((i-1)*10 +pendigits(17*i)+1)=1;
end








best_acc=0;
best_accfun='logsig';
best_structure=[3 5];
best_reg=0.1;
best_epoch=1000;
for structure = {[3 5],[10 10],[2 16],[12 8 12]}
     for k={'logsig','tansig','poslin'}
        for r={0.01,0.02,0.05,0.1,0.02}
            
     net = patternnet(structure{1});
    for i=1:length(structure{1})
     net.layers{i}.transferFcn = k{1};
    end
     net.performParam.regularization = r{1};
     
     net.divideFcn ='divideind';
    
     broj=round(0.8*Ntrain);
     net.divideParam.trainInd = 1:broj;
     net.divideParam.testInd =[];
     net.divideParam.valInd = broj+1:Ntrain;
    
     net.trainParam.max_fail =10;
    
     net.trainParam.goal = 0.001;
     net.trainParam.min_grad = 0.00001;
    
     net.trainParam.epochs =1000;
     net.trainparam.showWindow = false;
    
    
    
     [net, tr] = train(net,Xtrain,Ytrain);
    
     Xval = Xtrain(:,broj+1:Ntrain);
     Yval = Ytrain(:,broj+1:Ntrain);
    
     Yval_pred = net(Xval);
    
    [c, cm] = confusion(Yval, Yval_pred);
    cm  =cm';
    
     R = cm(1,1)/(cm(1,1)+cm(2,1));
     P = cm(1,1)/(cm(1,1)+cm(1,2));
     A =1-c;
    
     if A>best_acc
         best_acc=A;
         best_transferfcn=k{1};
         best_reg=r{1};
         best_structure=structure{1};
         best_epoch=tr.best_epoch;
     end
         
          
        end
     end
end


 net = patternnet(best_structure);
 for i=1 :length(best_structure)
     net.layers{i}.transferFCN=best_accfun;
 end
 net.performParam.regularization = best_reg;
net.trainParam.epochs=best_epoch;
net.trainParam.max_fail = 10;
net.trainParam.goal = 10e-9;
net.trainParam.min_grad = 10e-9;

 net.divideFcn ='';

    
net = train(net,Xtrain,Ytrain);

%% Testiranje NM nad test podacima
load pendigits.tes
pendigits=transpose(pendigits);
Xtest = pendigits(1:16, :);
Ntest = length(Xtest);

Ytest=zeros(10,Ntest);
for i=1:length(pendigits)
    Ytest((i-1)*10 +pendigits(17*i)+1)=1;
end
%%%%%% Predikaija NM nad trening skupom i prikaz matrice konfucije
Ytrain_pred = net(Xtrain);
figure
plotconfusion(Ytrain, Ytrain_pred);
[c, cm]=confusion(Ytrain,Ytrain_pred)
cm=cm';
ukupno_R=0;
ukupno_P=0;
disp("TRAINING SKUP:")
for i=1:10
    P=0;
    for j=1:10
        P=P+cm(i,j);
    end
    P=cm(i,i)/P;
    R=0;
    for j=1:10
    R=R+cm(j,i);
    end
    R=cm(i,i)/R;
    disp("Klasa "+i+" P="+P+",R="+R);
    ukupno_P=ukupno_P+P;
    ukupno_R=ukupno_R+R;
end
disp("Prosecno P= "+(P/10)+",Prosecno R="+(R/10));
%%%%%%

%%%%%% Predikaija NM nad test skupom i prikaz matrice konfucije
Ytest_pred = net(Xtest);
figure
plotconfusion(Ytest, Ytest_pred);


[c, cm] = confusion(Ytest, Ytest_pred);
cm = cm';

disp("TEST SKUP:")
for i=1:10
    P=0;
    for j=1:10
        P=P+cm(i,j);
    end
    P=cm(i,i)/P;
    R=0;
    for j=1:10
    R=R+cm(j,i);
    end
    R=cm(i,i)/R;
    disp("Klasa "+i+" P="+P+",R="+R);
    ukupno_P=ukupno_P+P;
    ukupno_R=ukupno_R+R;
end
disp("Prosecno P= "+(P/10)+",Prosecno R="+(R/10));
%%%%%%

disp("Najbolja funkcija= "+best_accfun);
disp("Najbolja struktura= "+best_structure);
disp("Najbolja regularizajica= "+best_reg);
disp("Najbolja epoha= "+best_epoch);

