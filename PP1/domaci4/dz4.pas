program project1(input,ulaz,izlaz);

type
    vlasnik = RECORD
    ime : string;
    datum : string;
    velicina_datoteke : integer;
    ime_datoteke : string;

    end;

var
  vl : vlasnik;
  ulaz,izlaz : text;
  ime_obrade,ime_ispisa:string;

procedure citajRec(var dat : text; var rec:string);

var
  c:char;

begin

  rec := '';
  read(dat,c);
  while ( c <> ' ') do begin

    rec := rec + c;
    read(dat,c);

  end;

end;

procedure ispis(var iz : text; zbir:real;br_dat :integer;tren_ime :string);

begin
  write(iz,tren_ime,' ');
  write(iz,zbir:2:2,' Kb ');
  write(iz,br_dat,' datoteke');
  writeln(iz);


end;

procedure obrada (var ul,iz : text;var vl : vlasnik);

var
  zbir:real;
  br_dat:integer;
  tren_ime:string;
  tacno:boolean;

begin
  zbir:=0;
  tacno:=false;
  while not eof(ul) do begin

    while not eoln(ul) do begin


      citajRec(ul, vl.ime);

      if (tren_ime = vl.ime) then begin

        citajRec(ul,vl.datum);
        read(ul,vl.velicina_datoteke);

        zbir:=zbir + vl.velicina_datoteke;

        br_dat:=br_dat+1;

        read(ul,vl.ime_datoteke);
        tacno:=true;

      end
      else begin

        if (tren_ime <> ' ') and (tacno) then begin
          zbir:=zbir/1024;

           ispis(iz,zbir,br_dat,tren_ime);
        end;

      tren_ime := vl.ime;

      zbir:=0;

      citajRec(ul,vl.datum);
      read(ul,vl.velicina_datoteke);

      zbir := zbir + vl.velicina_datoteke;
      br_dat :=1;

      read(ul,vl.ime_datoteke);
      tacno:=true;

      end;


    end;
    readln(ul);
  end;

end;

procedure ucitavanje(var ul,iz : text;ime_obrade,ime_ispisa:string);

  begin

    assign(ul,ime_obrade);
    reset(ul);

    assign(iz,ime_ispisa);
    rewrite(iz);

  end;

begin
  repeat

  write('Unesi ime datoteke sa kojom vrsimo obradu(obavezno dodajte ekstenziju datoteke {txt,doc...)): ');
  readln(ime_obrade);

  write('Unesi ime datoteke u koju ispisujemo rezultate obrade(obavezno dodajte ekstenziju datoteke {txt,doc...)): ');
  readln(ime_ispisa);

  if (ime_obrade = '') then
  exit;

  ucitavanje(ulaz,izlaz,ime_obrade,ime_ispisa);

  obrada(ulaz,izlaz,vl);
  close(ulaz);close(izlaz);

  until (ime_obrade = ''); ;

end.

