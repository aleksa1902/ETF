program dz5_pom(input,izlaz);

type vlasnik = RECORD
  lokacija : string[24];
  cena : real;
  stopa : real;
  godina : integer;
end;

var
  izlaz : file of vlasnik;
  v : vlasnik;
  i,n : integer;
  pom:string;
  imeFajla : string;
begin
     writeln('Unesite ime datoteke koju formirate: ');
     readln(imeFajla);

     if (imeFajla = '') then
     exit;

     writeln('Unesite broj lokacija koje upisujete: ');
     readln(n);

     assign (izlaz,imeFajla);
     rewrite(izlaz);
  for i := 1 to n do
      begin
        writeln('Novi Korisnik:');
        write('Lokacija: ');
        readln(v.lokacija);
         write('cena: ');
        readln(v.cena);
         write('stopa: ');
        readln(v.stopa);
        write('godina: ');
        readln(v.godina);

        write(izlaz, v);


      end;
     close(izlaz);
end.
