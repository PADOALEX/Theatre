import pathlib
import subprocess
import sys
import tempfile

def run(text,cwd):
    return subprocess.run([sys.argv[1]],input=text.encode(),cwd=cwd,capture_output=True,timeout=3,check=True).stdout.decode()

record='Hamlet\n01-01-2099\n19:00\n120\n1\n1\nJohn\nSmith\n5\nDrama\n0\n0\n---\n'
with tempfile.TemporaryDirectory() as cwd:
    assert run('',cwd)
    path=pathlib.Path(cwd,'performances.txt')
    path.write_text(record,encoding='ascii')
    output=run('7\nHamlet\nBuyer\n2\n0\n',cwd)
    assert 'Ticket sold successfully' in output
    assert 'Available Seats: 4' in output
    assert 'Seat Number: 5' in output
    output=run('7\nHamlet\nSecond buyer\n8\n9\n2\n0\n',cwd)
    assert 'Ticket ID: 2' in output and 'Available Seats: 3' in output
    assert 'Reload blocked' in output and 'Clear blocked' in output
    assert 'Ticket sold successfully' not in run('7\nHamlet\n',cwd)
    assert 'Available Seats: 3' in run('2\n0\n',cwd)
    path.write_text(record.replace('120\n1\n1\n','120\n1\n99999\n'),encoding='ascii')
    assert 'Hamlet' not in run('2\n0\n',cwd)
print('PASS: one seat per ticket, corrupt actor count rejected and EOF exit')
