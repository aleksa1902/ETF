program dz5;
    type vlasnik = RECORD
      lokacija : string[24];
      cena : real;
      stopa : real;
      godina : integer;
    end;

       pokCvor = ^cvor;

       cvor = RECORD
        kredit: vlasnik;
        sl : pokCvor;
      end;

procedure dodajNaKraj(var Gl:pokCvor; v:vlasnik);
 var
   pom, novi:pokCvor;

begin

  new(novi);
  novi^.sl := nil;
  novi^.kredit := v;

  if(Gl = nil)then begin
    Gl := novi;
    end
  else begin
     pom := Gl;
     while( pom^.sl <> nil ) do pom := pom^.sl;
     pom^.sl := novi;
   end;

end;

procedure  obrisiListu( var Gl:pokCvor);

var
   pom:pokCvor;

begin

  while(Gl <> nil) do begin
       pom := Gl;
       Gl := Gl^.sl;
       dispose(pom);
  end;
end;

function ukupnaCena(v:vlasnik):real;
var
   p:real;
   i:integer;

  begin

    p:=1;
    for i:=1 to v.godina do
        p:=p*(1+v.stopa/100);

    ukupnaCena := v.cena * p;
  end;

function ukupnaKamata(v:vlasnik):real;

   begin
    ukupnaKamata := ukupnaCena(v) - v.cena ;
  end;

procedure ucitajKredite(var Gl:pokCvor; imeFajla:string);

var
   v : vlasnik;
   ulaz : file of vlasnik;

begin

    assign(ulaz,imeFajla);
    reset(ulaz);
    while( not eof(ulaz) )do begin
         read(ulaz, v);
         dodajNaKraj(Gl, v);
    end;
     close(ulaz);

end;

procedure obrisiSveVece(var Gl:pokCvor; maxIznos:real);
  var
     pom, k:pokCvor;

begin
  while(Gl <> nil) AND (ukupnaCena(Gl^.kredit)>maxIznos) do begin
       pom := Gl;
       Gl := Gl^.sl;
       dispose(pom);
  end;

  pom := Gl;
  while (pom^.sl<>nil) do begin
       if(ukupnaCena(pom^.sl^.kredit)>maxIznos)  then begin
           k := pom^.sl;
           pom^.sl := k^.sl;
           dispose(k);
       end
       else begin
           pom := pom^.sl;
       end;
  end;
end;

procedure sortirajListu( var Gl:pokCvor );
  var
     p, k:pokCvor;
     v: vlasnik;

     begin
       p:=Gl;
       while p<>nil do begin
              k := p^.sl;
              while k<>nil do begin
                   if(ukupnaCena(p^.kredit) > ukupnaCena(k^.kredit))then begin
                         v := p^.kredit;
                         p^.kredit := k^.kredit;
                         k^.kredit := v;
                   end;
                   k := k^.sl;
              end;
              p:=p^.sl;;
       end;
     end;

procedure ispisKredita(v:vlasnik);

begin
  writeln(v.lokacija,' kosta: ',v.cena:2:2,' sa kamatnom stopom od ',v.stopa:2:2,' % na ',v.godina,' godina => ukupno: ',ukupnaCena(v):2:2);
end;

procedure  ispisListe(Gl:pokCvor);

begin
  while(Gl <> nil) do begin
       ispisKredita(Gl^.kredit);
       Gl := Gl^.sl;
  end;
end;

procedure ispisUdatoteku(Gl :pokCvor;imeFajla2:string);

var
   izlaz : text;
   v : vlasnik;
begin
  assign(izlaz,imeFajla2);
  rewrite(izlaz);

  while(Gl <> nil) do begin
       writeln(izlaz,Gl^.kredit.lokacija ,' ',Gl^.kredit.cena:2:2,' ',Gl^.kredit.stopa:2:2,' ',Gl^.kredit.godina,'  ' ,'Ukupno : ',ukupnaCena(Gl^.kredit):2:2);
       Gl := Gl^.sl;
  end;
  close(izlaz);
end;

var
   Gl : pokCvor;
   imeFajla,imeFajla2: string;
   maxIznos:real;
begin

  Gl := nil;
  writeln('Unesite ime Fajla za ucitavanje: ');
  readln(imeFajla);
  writeln('====================================================================================================================');

  while (imeFajla <> '') do begin                     {sve dok za ime fajla ne unesemo nista}
          ucitajKredite(Gl, imeFajla);
          ispisListe(Gl);

          writeln('====================================================================================================================');
          write('Unesite max Iznos: ');
          readln(maxIznos);
          obrisiSveVece(Gl, maxIznos);
          sortirajListu(Gl);

          writeln('====================================================================================================================');
          writeln('Unesite ime Fajla za ispisivanje: ');
          readln(imeFajla2);
          ispisUdatoteku(Gl,imeFajla2);

          obrisiListu(Gl);

          writeln('Ispisivanje zavrseno,mozete pogledati rezultate u ',imeFajla2);

          writeln('====================================================================================================================');
          writeln('Unesite ime Fajla: ');
          readln(imeFajla);

  end;

  readln();

end.
