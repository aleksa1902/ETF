program dz2_mod(input,ouutput);

const
  MAX = 100;

type
  niz = array [1..MAX] of real;

var
  a : niz;
  n :integer;     {broj clanova}
  ab, b, c,k : integer;  {brojaci k sluzi da izracunavanje novonastalog niza}
  veci_clanovi, manji_clanovi :  integer;
  asredina : real;
  mincl,maxcl : real; {minimalni clan i maksimalni clan}


begin
     writeln(output, 'Unesi broj clanova koliko zelis da ovaj niz ima: ');
     read (input,  n);

     while (n > 0) and (n <= MAX) do begin

           for ab := 1 to n do

               begin
                    writeln(output, 'Unesi ', ab , ' clan niza: ');
                    readln(input, a[ab])
               end;


           for ab := 1 to n-1 do

               for b := ab+1 to n do

                   begin
                        asredina := (a[ab] + a[b]) / 2;

                        veci_clanovi := 0;
                        manji_clanovi := 0;


                        for c := 1 to n do

                            if (c <> ab) and (c <> b) then

                            begin

                               if ( asredina < a[c]) then
                                  manji_clanovi := manji_clanovi + 1;
                               if ( asredina > a[c]) then
                                  veci_clanovi := veci_clanovi + 1;

                            end;

                   if ( veci_clanovi = manji_clanovi) then

                      begin

                         writeln(output,'Par sa aritmetickom sredinom: ');

                         writeln (output, a[ab]:0:0, ' , ',a[b]:0:0);

                      end;





                   end;    {kraj petlje za izracunavanje as}

           maxcl := a[1];
           mincl := a[1];

           for ab := 2 to n do                 {proverava koji je clan max}
               if (a[ab] > maxcl) then

                  begin
                       maxcl := a[ab];
                  end;

           for ab := 2 to n do
               if (a[ab] < mincl) then       {proverava koji je clan min}

                  begin
                       mincl := a[ab];
                  end;

           k := 1;
           for ab :=1 to n do
               if(a[ab] <> mincl) and (a[ab] <> maxcl) then

                  begin

                       a[k] := a[ab];       {sa novim brojacem izbacujem max i min}
                       k := k+1;

                  end;

           n := k-1;                            {posto gore imam k:=k+1 on ce mi dodati bespotrebno novi clan u kom nece biti nista pa ga izbacujemo}

           writeln(output,'Trenuni broj clanova koji sacinjavaju novi niz je ', n);

           write(output,'Novi niz je: ');
           for ab := 1 to n do
               write(output,a[ab]:3:2,' ,');

          readln;

     end;  {kraj while petlje}


end.

