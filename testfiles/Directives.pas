program Directives;
begin
{$ifdef NANOPASCAL}
    writeln('Hello World from NanoPascal');
{$else}
    writeln('Hello World from Other Pascal Compiler');
{$endif}
end. 
