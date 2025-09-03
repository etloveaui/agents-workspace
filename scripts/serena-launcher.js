#!/usr/bin/env node
import { spawn } from 'child_process';
import { platform, homedir } from 'os';
import { existsSync } from 'fs';
import { join } from 'path';

function findSerenaExecutable() {
  const possiblePaths = [];
  
  if (platform() === 'win32') {
    possiblePaths.push(
      join(homedir(), '.local', 'bin', 'serena-mcp-server.exe'),
      join(homedir(), '.cargo', 'bin', 'serena-mcp-server.exe'),
      'serena-mcp-server.exe'
    );
  } else {
    possiblePaths.push(
      join(homedir(), '.local', 'bin', 'serena-mcp-server'),
      join(homedir(), '.cargo', 'bin', 'serena-mcp-server'),
      'serena-mcp-server'
    );
  }
  
  for (const path of possiblePaths) {
    if (existsSync(path)) {
      return path;
    }
  }
  
  throw new Error('Serena MCP server not found. Please install it first.');
}

try {
  const serenaPath = findSerenaExecutable();
  const child = spawn(serenaPath, process.argv.slice(2), {
    stdio: 'inherit',
    shell: false
  });
  
  child.on('error', (err) => {
    console.error('Failed to start Serena:', err.message);
    process.exit(1);
  });
  
  child.on('exit', (code) => {
    process.exit(code || 0);
  });
} catch (error) {
  console.error(error.message);
  process.exit(1);
}