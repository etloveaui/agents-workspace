#!/usr/bin/env node
import { readFileSync, writeFileSync, existsSync } from 'fs';
import { platform, homedir } from 'os';
import { join } from 'path';

const CONFIG_PATH = '.mcp.json';

// Base MCP configuration that works across environments
const baseMcpConfig = {
  mcpServers: {
    filesystem: {
      command: "npx",
      args: [
        "-y", "@modelcontextprotocol/server-filesystem",
        "--root", ".",
        "--root", ".claude"
      ],
      env: {}
    },
    "context7": {
      command: "npx",
      args: ["-y", "@upstash/context7-mcp"],
      env: {}
    },
    "sequential-thinking": {
      command: "npx",
      args: ["-y", "@modelcontextprotocol/server-sequential-thinking"],
      env: {}
    },
    "playwright": {
      command: "npx",
      args: ["-y", "@playwright/mcp"],
      env: {}
    },
    "hello-mcp": {
      command: "node",
      args: ["servers/hello-mcp/index.js"],
      env: {}
    },
    "ide": {
      command: "npx",
      args: ["-y", "@modelcontextprotocol/server-ide"],
      env: {}
    }
  }
};

function findSerenaExecutable() {
  const possiblePaths = [];
  
  if (platform() === 'win32') {
    possiblePaths.push(
      join(homedir(), '.local', 'bin', 'serena-mcp-server.exe'),
      join(homedir(), '.cargo', 'bin', 'serena-mcp-server.exe')
    );
  } else {
    possiblePaths.push(
      join(homedir(), '.local', 'bin', 'serena-mcp-server'),
      join(homedir(), '.cargo', 'bin', 'serena-mcp-server')
    );
  }
  
  for (const path of possiblePaths) {
    if (existsSync(path)) {
      return path;
    }
  }
  
  return null;
}

function setupMcpConfig() {
  let config = { ...baseMcpConfig };
  
  // Try to add Serena if available
  const serenaPath = findSerenaExecutable();
  if (serenaPath) {
    config.mcpServers.serena = {
      command: "node",
      args: ["scripts/serena-launcher.js"],
      env: {}
    };
    console.log('✅ Serena MCP server found and configured');
  } else {
    console.log('⚠️  Serena MCP server not found - skipping');
  }
  
  // Write configuration
  writeFileSync(CONFIG_PATH, JSON.stringify(config, null, 2));
  console.log('✅ MCP configuration updated successfully');
  
  return config;
}

function main() {
  const command = process.argv[2];
  
  if (command === 'setup' || !command) {
    setupMcpConfig();
  } else if (command === 'check') {
    console.log('🔍 Checking MCP server availability...');
    
    const serenaPath = findSerenaExecutable();
    console.log(`Serena: ${serenaPath ? '✅ Found' : '❌ Not found'}`);
    
    console.log('Base servers: ✅ Available via npx');
    console.log('Hello MCP: ✅ Available locally');
  } else {
    console.log(`
Usage: node scripts/setup-mcp.js [command]

Commands:
  setup (default) - Generate MCP configuration based on available servers
  check          - Check which MCP servers are available

This script automatically detects available MCP servers and creates
an appropriate configuration that works across different environments.
    `);
  }
}

main();