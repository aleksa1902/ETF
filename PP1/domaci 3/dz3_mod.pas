program dz3_mod(input,output);

const
  MAX_CL = 40;
  MAX = 255;

type
  matrica = array [1..MAX_CL,1..MAX_CL] of integer;
  skup = set of 1..MAX;

var
  a : matrica;
  m,n : integer;
  s : skup;
  nema : boolean;

procedure upis(var m,n:integer; var a: matrica; var nema: boolean);

var
   i, j : integer;

begin
  write(output,'Unesite broj vrsta i broj kolona koliko zelite da ima ova matrica: ');
  readln(input,m,n);

  if ( m > MAX_CL) or (n > MAX_CL) or ( m < 0 ) or ( n < 0) then
     begin

       nema := true;
       exit;

     end;

  writeln(output,'Unesite matricu sa njenim clanovima ');

  for i := 1 to m do
      for j := 1 to n do

          read( a[i,j] );

end;
procedure unosuskup(var s:skup);
const
  MAX = 255;
var
   i : integer;

begin

   for i := 1 to MAX do                   {unosim brojeve od 1 do 255 u skup}

         s := s + [i];

end;

procedure ispis(n,x:integer; a: matrica);

var
  i : integer;

begin

  writeln(output,'Vrsta simetricne matrice je: ');

  for i := 1 to n do

      write (output, a[x,i], ' ');

  writeln();

end;

procedure provera(m,n:integer; a : matrica;s:skup);

var
   x, i, j : integer;
   palin,prekor : boolean;

begin

  for x := 1 to m do
      begin

        palin := true;
        prekor := true;
        i := 1;
        j := n;


        while palin and prekor do
              begin

                if not( a[x,i] in s) or not(a[x,j] in s) then          {ako brojevi nisu u skupu onda automatski prekidam while petlju sa false}
                   palin := false;

                if ( a[x,i] <> a[x,j]) then
                   palin := false;

                if ( i >= j ) then
                   prekor := false;

                inc(i);
                j := j - 1;

              end;

        if ( palin = true) then
           ispis(n,x,a);

      end;

end;

begin

  repeat

  upis(m,n,a,nema);

  if ( nema = true) then
     exit;

  unosuskup(s);

  provera(m,n,a,s);

  writeln(output,'==============================================================================');

  until nema = true;
end.
