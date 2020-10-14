clc, clear, close all

%% Ucitavanje odbiraka
name = 'pendigits.tes';
load(name);

pendigits_test=pendigits;
pendigits_test=transpose(pendigits_test);
ulaz_test = pendigits_test(1:16, :);
izlaz_test = pendigits_test(17, :);


name = 'pendigits.tra';
load(name);
pendigits_tra=pendigits;
pendigits_tra=transpose(pendigits_tra);
ulaz_tra = pendigits_tra(1:16, :);
izlaz_tra = pendigits_tra(17, :);


K0_test = ulaz_test(:, izlaz_test == 0);
K1_test = ulaz_test(:, izlaz_test == 1);
K2_test= ulaz_test(: ,izlaz_test==2);
K3_test = ulaz_test(:, izlaz_test == 3);
K4_test= ulaz_test(: ,izlaz_test==4);
K5_test = ulaz_test(:, izlaz_test == 5);
K6_test= ulaz_test(: ,izlaz_test==6);
K7_test = ulaz_test(:, izlaz_test == 7);
K8_test= ulaz_test(: ,izlaz_test==8);
K9_test = ulaz_test(:, izlaz_test == 9);

K0_tra = ulaz_tra(:, izlaz_tra == 0);
K1_tra = ulaz_tra(:, izlaz_tra == 1);
K2_tra= ulaz_tra(: ,izlaz_tra==2);
K3_tra = ulaz_tra(:, izlaz_tra == 3);
K4_tra= ulaz_tra(: ,izlaz_tra==4);
K5_tra = ulaz_tra(:, izlaz_tra == 5);
K6_tra= ulaz_tra(: ,izlaz_tra==6);
K7_tra = ulaz_tra(:, izlaz_tra == 7);
K8_tra= ulaz_tra(: ,izlaz_tra==8);
K9_tra = ulaz_tra(:, izlaz_tra == 9);

n0=size(K0_test,2)+size(K0_tra,2);
n1=size(K1_test,2)+size(K1_tra,2);

n2=size(K2_test,2)+size(K2_tra,2);
n3=size(K3_test,2)+size(K3_tra,2);

n4=size(K4_test,2)+size(K4_tra,2);
n5=size(K5_test,2)+size(K5_tra,2);

n6=size(K6_test,2)+size(K6_tra,2);
n7=size(K7_test,2)+size(K7_tra,2);

n8=size(K8_test,2)+size(K8_tra,2);
n9=size(K9_test,2)+size(K9_tra,2);

%% Prikaz podataka
figure, hold all
plot([0 0],[0 n0]);
plot([1 1],[0 n1]);

plot([2 2],[0 n2]);
plot([3 3],[0 n3]);

plot([4 4],[0 n4]);
plot([5 5],[0 n5]);

plot([6 6],[0 n6]);
plot([7 7],[0 n7]);

plot([8 8],[0 n8]);
plot([9 9],[0 n9]);
legend(""+n0,""+n1,""+n2,""+n3,""+n4,""+n5,""+n6,""+n7,""+n8,""+n9);
xlabel("Klasni tip");
ylabel("Broj instanci klase");
%plot([4 4],[0 size(K4_test,2)+size(K4_tra,2)],'p-');
%plot([5 5],[0 size(K5_test,2)+size(K5_tra,2)],'y-');

